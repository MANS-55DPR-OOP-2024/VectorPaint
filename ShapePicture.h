#ifndef _VectorPaint_Picture_h_
#define _VectorPaint_Picture_h_

#include <CtrlLib/CtrlLib.h>

class ShapePicture{
	private:
		vector <Shape*>shps;
		
	public:
		~ShapePicture(){
			for(int i=0;i<shps.size();i++)
				delete shps[i];	
		}
		
		void paint(Draw& w){
			for(int i=0;i<shps.size();i++)
				shps[i]->paint(w);
		}
		
		int size(){
			return shps.size();
		}
		
		Shape* getShape(int i){
			if(i<size())
				return shps[i];
			else
				return NULL;
		}
		
		Shape* addShape(string kind){
			Shape *sp=NULL;
			//TODO add names for new figures
			if(kind=="line") sp=new Line();
			if(kind=="tri") sp=new Triangle();
			if(kind=="frc") sp=new Mandelbrot();
			
			if(sp!=NULL)shps.push_back(sp);
			else Upp::PromptOK("unknown shape: "<<kind);
			return sp;
		}
		

		
		
	
};

#endif
