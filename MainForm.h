#ifndef _VectorPaint_MainForm_h_
#define _VectorPaint_MainForm_h_

#include <CtrlLib/CtrlLib.h>
#include "PictureController.h"
#include "ShapePicture.h"
#include "Propertys.h"



#define LAYOUTFILE <VectorPaint/MainForm.lay>
#include <CtrlCore/lay.h>

using namespace Upp;


//Главная форма программы
//содержит изображение

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
			
			//тут привязаны обработчики нажатий на кнопки формы
			addLineButton<<[=] { 
				Shape*shp= pict.addShape("line");
				pictController.startInput(shp);
				updateList();
			};
			
			addTriButton<<[=] { 
				Shape*shp= pict.addShape("tri");
				pictController.startInput(shp);
				updateList();
			};
			addFrciButton<<[=] { 
				Shape*shp= pict.addShape("frc");
				pictController.startInput(shp);
				updateList();
			};
			
			addTextButton<<[=]{
				Shape*shp= pict.addShape("text");
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
			
			proprtySelected<<[=]{
				int c=nameList.GetCursor();
				if(c>=0){
					PropertyHelper::showDialog(pict.getShape(c));	
					updateList();
					nameList.SetCursor(c);
				}
			};	
			
			
		}
};


#endif