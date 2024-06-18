
#include <CtrlLib/CtrlLib.h>

using namespace Upp;
using namespace std;

class Shape{
	protected:
		string name;
		Color color;
		bool selected;
		vector<Point> points;
	public:
		Shape(string nm):name(nm){}
		virtual ~Shape(){}
		void setSelect(bool sel){
			selected=sel;
		}
		int size(){
			return points.size();
		}
		void setponit(int i, Point pnt){
			if(i<points.size()) points[i]=pnt;
		}
		string getName(){
			return name;
		}
		void setColor(Color cl){
			color=cl;
		}
		virtual void paint(Draw& w)=0;
		virtual void moveto(Point to)=0;
		
		
};

class Line: public Shape{
	public:
		Line(string name="line"):Shape(name){
			points.push_back(Point(100,100));
			points.push_back(Point(300,300));
			
	
			color=Black();
		}
		
		virtual void paint(Draw& w){
			w.DrawLine(points[0], points[1],
				selected?3:1,
				color);
		}
		
		virtual void moveto(Point to){
			int dx=points[0].x-points[1].x;
			int dy=points[0].y-points[1].y;
			
			points[0]=to;
			points[1]=Point(to);
			points[1].Offset(-dx,-dy);
		}
};

class Triangle: public Line{
	public:
		Triangle(string name="triangle"):Line(name){
			points.push_back(Point(100,300));
			
			color=Red();
		}
		virtual void paint(Draw& w){
			w.DrawLine(points[0], points[1],selected?3:2,color);	
			w.DrawLine(points[1], points[2],selected?3:2,color);
			w.DrawLine(points[2], points[0],selected?3:2,color);
		}
		
		virtual void moveto(Point to){
			int dx=points[0].x-points[1].x;
			int dy=points[0].y-points[1].y;
			int dx1=points[0].x-points[2].x;
			int dy1=points[0].y-points[2].y;
			
			points[0]=to;
			points[1]=Point(to);
			points[1].Offset(-dx,-dy);
			points[2]=Point(to);
			points[2].Offset(-dx1,-dy1);
		}
};