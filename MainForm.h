#ifndef _VectorPaint_MainForm_h_
#define _VectorPaint_MainForm_h_

#include <CtrlLib/CtrlLib.h>
#include "PictureController.h"
#include "ShapePicture.h"
#include "Propertys.h"
#include "Operations.h"



#define LAYOUTFILE <VectorPaint/MainForm.lay>
#include <CtrlCore/lay.h>

using namespace Upp;


//Главная форма программы
//содержит изображение

class MainForm : public  WithMainFormLayout<TopWindow>  {
	private:
		MenuBar menu;
		ToolBar tool;
		ShapePicture pict;	
		
		void updateList(bool newshape=false){
			int c=nameList.GetCursor();
			nameList.Clear();
			for(int i=0;i<pict.size();i++){
				nameList.Add(pict.getShape(i)->getName());
			}
			if(newshape)
				nameList.SetCursor(pict.size()-1);
			else
				nameList.SetCursor(c);
		}
		
		void updateSelected(){
			int c=nameList.GetCursor();
			for(int i=0;i<pict.size();i++)
				pict.getShape(i)->setSelect(i==c);
		}
		
		void Exit() {
			if(PromptOKCancel("Exit Paint?"))
				Break();
		}
		
		void SubMenu(Bar& bar) {
			bar.Add("Exit", [=] { Exit(); });
		}

		void MainMenu(Bar& bar) {
			bar.Sub("Menu", [=](Bar& bar) { SubMenu(bar); });
		}

		void SubBar(Bar& bar) {
			bar.Add("Add line", Upp::CtrlImg::wheel_cursor() , [=] { BarFn(); });
			bar.Add("Exit", Upp::CtrlImg::remove(),  [=] { Exit(); });
		}
		void MenuFn() {
			PromptOK("Fn activated!");
		}
		
		void BarFn() {
			Shape*shp= pict.addShape("line");
			pictController.startInput(shp);
			updateList(true);
		}
		
	public:
		MainForm(){
			CtrlLayout(*this, "Vector paint");
			Zoomable().Sizeable();
			
			pictController.init(&pict);
			
			//TODO тут привязаны обработчики нажатий на кнопки формы
			addLineButton<<[=] { 
				Shape*shp= pict.addShape("line");
				pictController.startInput(shp);
				updateList(true);
			};
			
			addTriButton<<[=] { 
				Shape*shp= pict.addShape("tri");
				pictController.startInput(shp);
				updateList(true);
			};
			
			addFrciButton<<[=] { 
				Shape*shp= pict.addShape("frc");
				pictController.startInput(shp);
				updateList(true);
			};
			
			addTextButton<<[=]{
				Shape*shp= pict.addShape("text");
				pictController.startInput(shp);
				updateList(true);
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
				}
			};
			
			nameList.WhenSel<<[=]{
				updateSelected();	
				Refresh();
			};	
			
			rotateButton<<[=]{
				int c=nameList.GetCursor();
				if(c>=0){
					OperationsHelper::rotate(pict.getShape(c), 10);	
					Refresh();	
				}
			};
			
			rotateLeftButton<<[=]{
				int c=nameList.GetCursor();
				if(c>=0){
					OperationsHelper::rotate(pict.getShape(c), -10);	
					Refresh();	
				}
			};
			
			scaleButton<<[=]{
				int c=nameList.GetCursor();
				if(c>=0){
					OperationsHelper::scale(pict.getShape(c), 1.5);	
					Refresh();	
				}
			};
			scaleLeftButton<<[=]{
				int c=nameList.GetCursor();
				if(c>=0){
					OperationsHelper::scale(pict.getShape(c), 1.0/1.5);	
					Refresh();	
				}
			};
			
			//Добавление главного меню
			AddFrame(menu);
       		menu.Set([=](Bar& bar) { MainMenu(bar); });
       		
       		//Добавление панели инструментов
       		AddFrame(tool);
       		tool.Set([=](Bar& bar) { SubBar(bar); });
       		
		}
};


#endif