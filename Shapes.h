#ifndef _VectorPaint_Shapes_h_
#define _VectorPaint_Shapes_h_

#include <CtrlLib/CtrlLib.h>


using namespace Upp;
using namespace std;


//Базовая фигура
//состоит из масива точек, имени и цвета фигуры

class Shape  {
	friend class OperationsHelper;
	
	protected:
		string name;
		Color color;
		int width;
		
		bool selected;
		vector<Point> points;
	public:
		Shape(string nm):name(nm),width(1),selected(true){}
		virtual ~Shape(){}

		void setSelect(bool sel){
			selected=sel;
		}
		int size(){
			return points.size();
		}
		virtual void setponit(int i, Point pnt){
			if(i<points.size()) points[i]=pnt;
		}
		string getName(){
			return name;
		}
		void setName(string an){
			name=an;
		}
		Color getColor(){
			return color;
		}
		void setColor(Color cl){
			color=cl;
		}
		int getWidth(){
			return width;
		}
		void setWidth(int w){
			width=w;
		}
		virtual void paint(Draw& w){
			if(selected)
				for(int i=0;i<size();i++)
					w.DrawEllipse(points[i].x-5, points[i].y-5, 10, 10, Red());
		}
		virtual void moveto(Point to)=0;
};


//Наследник базовой фигуры
//Линия - две точки
class Line: public Shape{
	public:
		Line(string name="line"):Shape(name){
			points.push_back(Point(100,100));
			points.push_back(Point(300,300));
			
			color=Black();
		}
		
		virtual void paint(Draw& w){
			Shape::paint(w);
			
			w.DrawLine(points[0], points[1], width, color);
		}
		
		virtual void moveto(Point to){
			int dx=points[0].x-points[1].x;
			int dy=points[0].y-points[1].y;
			
			points[0]=to;
			points[1]=Point(to);
			points[1].Offset(-dx,-dy);
		}
};

//Наследник Линии, состоит из трех точек

class Triangle: public Line{
	public:
		Triangle(string name="triangle"): Line(name){
			points.push_back(Point(100,300));
			
			color=Red();
		}
		virtual void paint(Draw& w){
			Shape::paint(w);
			
			w.DrawLine(points[0], points[1], width, color);	
			w.DrawLine(points[1], points[2], width, color);
			w.DrawLine(points[2], points[0], width, color);
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

//Фигура текст
class TextShape: public Shape{
	public:
		TextShape(string name="text"):Shape(name){
			points.push_back(Point(100,100));
			
			color=Green();
		}
		
		virtual void paint(Draw& w){
			Shape::paint(w);
			
			w.DrawText(points[0].x, points[0].y, name, Arial(10+width), color);
		}
		
		virtual void moveto(Point to){
			points[0]=to;
		}
};


//Фрактал Мандельброта
//задается двумя точками

class Mandelbrot: public Line{
	private:
		Image img;
		long double scale=0;
		long double yscale=0;
		const int maxIt=100;
		int num_iters(double cx, double cy) {
	        std::complex<double> z(0.0, 0.0);
	        std::complex<double> c(cx, cy);
	        for (int i = 0; i <= maxIt; ++i) {
	            if (std::abs(z) > 2.0) return i;
	            z = z * z + c;
	        }
	        return maxIt;
		}
		
	public:
		Mandelbrot(string name="mandelbrot"):Line(name){
			update();
		}
		
		virtual void setponit(int i, Point pnt){
			Shape::setponit(i,pnt);
			
			update();
		}
		
		virtual void paint(Draw& w){
			Shape::paint(w);
			
			w.DrawImage(points[0].x, points[0].y, img);
		}
		
		void update(){
			int width = points[1].x - points[0].x;
			int height = points[1].y - points[0].y;
			if(width<=0||height<=0)return;
			
			ImageBuffer ib(width, height);
			RGBA* t = ~ib;
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					double cx = (double)x/ width*2.0/(1.0+scale) - 1.5;
					double cy = (double)y/ height*2.0/(1.0+yscale) - 1.0;
					int iterations = num_iters(cx, cy);
					Color color = HsvColorf(double(1.0/iterations) , 1, (iterations < maxIt));
					*t++ = color;
				}
			}
			img = ib;
		}
		
		long double& getScale(){
			return scale;
		}
		long double& getYScale(){
			return yscale;
		}
};


#endif
