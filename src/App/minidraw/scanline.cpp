#include "scanline.h"
#include<iostream>

using namespace minidraw;

CScanLine::CScanLine(Figure* p_polygon)
{
	this->p_polygon = p_polygon;
	InitInfo();
	FillPolygon();  // get mat_inside
}

CScanLine::~CScanLine()
{
}

void CScanLine::InitInfo()
{
	top = INT_MIN;
	bottom = INT_MAX;
	left = INT_MAX;
	right = INT_MIN;
	for(auto iter : p_polygon->p_point_array)
	{
		if (iter.x() < left)
			left = iter.x();
		if (iter.x() > right)
			right = iter.x();
		if (iter.y() > top)
			top = iter.y();
		if (iter.y() < bottom)
			bottom = iter.y();
	}

	width = right - left + 1;
	height = top - bottom + 1;
}

void CScanLine::BuildET()
{
	edge_table.resize(top - bottom + 1);
	int count = p_polygon->p_point_array.size(); // should equal to the size of vertices

	for (int i = 0; i < count; i++)
	{
		CEdge e;

		auto p = p_polygon->p_point_array[i];
		auto q = p_polygon->p_point_array[(i + 1) % count];

		if (p.y() == q.y())  // horizontal line. 
		{
			e.x = p.x();
			e.ymax = p.y(); 
			e.dx = 999999999;
			edge_table[p.y() - bottom].insert(edge_table[p.y() - bottom].end(), e);
			e.x = q.x();
			e.ymax = q.y();
			e.dx = 999999999;
			edge_table[q.y() - bottom].insert(edge_table [q.y() - bottom] .end(), e);
		}
		else
		{
			//找边的y较小的顶点为p, 较大的为q
			if (q.y() < p.y())
				std::swap(p, q);
			e.x = p.x();
			e.ymax = q.y();
			if (q.y() == p.y())  // perpendicular to x axis
			{
				e.dx = 0;
			}
			else
			{
				e.dx = (q.x() - p.x()) / (double)(q.y() - p.y());
			}
			edge_table[p.y() - bottom].insert(edge_table[p.y() - bottom].end(), e);
		}
	}
}

void CScanLine::UpdateAET(int aheight)
{
	std::list<CEdge>::iterator iter = active_edge_table.begin();

	// erase 
	while (iter != active_edge_table.end())
	{
		if (iter->ymax < aheight)  
		{
			iter = active_edge_table.erase(iter);
		}
		else
			iter++;
	}
	
	iter = active_edge_table.begin();
	while (iter != active_edge_table.end())
	{
		iter->x += iter->dx;
		iter++;
	}
	// add new edges 
	active_edge_table.insert(active_edge_table.end(), edge_table[aheight - bottom].begin(), edge_table[aheight - bottom].end());

	active_edge_table.sort();
}

/* Used to consider the boundary condition */
void CScanLine::CalcIntersects(int aheight)
{
	intersects.clear();
	if (active_edge_table.empty())
		return;

	std::list<CEdge>::iterator iter = active_edge_table.begin(), iter2;
	while (iter != active_edge_table.end()) // active_edge_table cannot only have one line
	{
		iter2 = iter;
		iter2++;
		if (active_edge_table.end() == iter2)
		{
			intersects.push_back(iter->x);
			iter++;
		}
		else if (fabs(iter->x - iter2->x) > 1e-2)
		{
			intersects.push_back(iter->x);
			iter++;
		}
		else // iter->x == iter2->x
		{
			if ((iter->ymax == aheight) && (iter2->ymax == aheight))
			{
				intersects.push_back(iter->x);
				intersects.push_back(iter->x);
			}
			else if ((iter->ymax > aheight) && (iter2->ymax > aheight))
			{

			}
			else // 不是极值点
			{ 
				intersects.push_back(iter->x); // 只放x坐标
			}
			iter++;
			iter++;
		}
	}
	std::sort(intersects.begin(), intersects.end());
}

void CScanLine::FillPolygon()
{
	BuildET();
	std::vector<int> intPts;  // 存放内部线的两端

	// scan 
	for (int i = bottom; i <= top; i++)
	{
		UpdateAET(i);
		CalcIntersects(i);

		bool status = false;				//初始在外
		intPts.clear();

		for (int j = 0; j < intersects.size(); j++)
		{
			if (intPts.empty())
				intPts.push_back((int)intersects[j]);  // x坐标
			else if ((int)intersects[j] == intPts.back())
			{
				intPts.pop_back();  //相邻两个重合的交点相互抵消
			}
			else
				intPts.push_back((int)intersects[j]);
		}
		intPts.push_back(INT_MAX);
		//std::cout << "inPts size() = " << intPts.size() << std::endl;
		
		int index = 0;
		for (int j = left - 1; j <= right; j++)
		{
			if (j == intPts[index])
			{
				status = !status;								//内外状态反转
				index++;
			}
			mat_inside[std::pair<int,int>(j,i)] = status;
			/*if (status)
			{
				if (j > 0 && j < width && i > 0 && i < height)
					mat.at<cv::uint8_t>(i, j) = 1;
			}*/
		}
	}
	//assert(mat_inside.size() == height * width);
}


float CScanLine::GetRectArea()
{
	return width * height;
}
