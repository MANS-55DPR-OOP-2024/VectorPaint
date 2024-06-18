#ifndef _VectorPaint_Picture_h_
#define _VectorPaint_Picture_h_



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
		
		Shape* addLine(){
			Line*ln=new Line();
			shps.push_back(ln);
			return ln;
		}
		
		Shape* addTriangle(){
			Triangle*ln=new Triangle();
			shps.push_back(ln);
			return ln;
		}
		
		
	
};

#endif
