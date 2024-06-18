#ifndef _VectorPaint_MainForm_h_
#define _VectorPaint_MainForm_h_

#include <CtrlLib/CtrlLib.h>
#include "PictureController.h"
#include "ShapePicture.h"

#define LAYOUTFILE <VectorPaint/MainForm.lay>
#include <CtrlCore/lay.h>

using namespace Upp;


class MainForm : public  WithMainFormLayout<TopWindow>  {
	private:
		ShapePicture pict;	
		
		void updateList(){
			nameList.Clear();
			for(int i=0;i<pict.size();i++)
				nameList.Add(pict.getShape(i)->getName());
		}
	public:
		MainForm(){
			CtrlLayout(*this, "Vector paint");
			Zoomable().Sizeable();
			
			pictController.init(&pict);
			
			addLineButton<<[=] { 
				Shape*shp= pict.addLine();
				pictController.startInput(shp);
				updateList();
			};
			
			addTriButton<<[=] { 
				Shape*shp= pict.addTriangle();
				pictController.startInput(shp);
				updateList();
			};
			
			moveSelected<<[=]{
				if(nameList.GetCursor()>=0){
					pictController.startMove(pict.getShape(nameList.GetCursor()));	
				}
			};
			
			resizeSelected<<[=]{
				if(nameList.GetCursor()>=0){
					pictController.startResize(pict.getShape(nameList.GetCursor()));	
				}
			};	
		}
};


#endif