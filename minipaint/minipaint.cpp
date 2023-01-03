/* This Program aims at making a small term duplicate of the well known -Microsoft PaintBrush-
(c) Microsoft Inc. */


#include<stdio.h>
#include<afxwin.h>
#include<afxext.h>
#include"resource.h"
#include<math.h>


struct desc_list
{
	char draw_mode;
	int pen_width;
	int pen_style;
	int color;
}modelist;



typedef class imagebuffer 
{
public:
	int mrows,mcols;
	int buf[300][300];
}imagebuffer;

imagebuffer buf1;




class dialog_PenWidth:public CDialog
{
public:

	dialog_PenWidth(int n):CDialog(n)
	{
	}

	int OnInitDialog()
	{
		CDialog::OnInitDialog();
		CheckRadioButton(2,6,2);
		return TRUE;
	}

	void OnOK()
	{
		CDialog::OnOK();
		modelist.pen_width=GetCheckedRadioButton(2,6)-1;
	}

	void OnCancel()
	{
		CDialog::OnCancel();
	}
};



class myframe:public CFrameWnd
{
private:

	CToolBar t_width,t_color,t_draw,t_pstyle;
	int visible_Wbar,visible_Cbar,visible_Dbar,visible_PSbar;
	CPoint startpoint,endpoint,betweenpt;
	CMenu mymenu;
	int check1,check2,check3,check4;
	int flag; //used for polygon drawing

	int flag2;//used for cursor control


	CStatusBar st_bar;

public:
	
	myframe()
	{
		CString mywindowclass;
		CBrush mybrush;
		
		
		
		
		mybrush.CreateSolidBrush(RGB(255,255,255));

		mywindowclass=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,AfxGetApp()->LoadStandardCursor(IDC_ARROW),mybrush,0);
		
		Create(mywindowclass,"MiniPaint - (c) Prashant 2002");
		check1=check2=check3=check4=1;
	}

	int OnCreate(LPCREATESTRUCT l)
	{
		CFrameWnd::OnCreate(l);
		
		flag2=0;
		flag=0;

		mymenu.LoadMenu(IDR_MENU1);
		SetMenu(&mymenu);
		t_width.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_TOP|
		CBRS_BORDER_TOP|CBRS_BORDER_BOTTOM|CBRS_BORDER_LEFT|CBRS_BORDER_RIGHT) ;
		ShowControlBar(&t_width,TRUE,FALSE);
		t_width.LoadToolBar(IDR_TOOLBAR3);

		
		for(int i=0;i<5;i++)
		t_width.SetButtonStyle(i,TBBS_CHECKGROUP);

		t_color.Create(this,WS_CHILD|WS_VISIBLE|CBRS_TOP|
			CBRS_BORDER_TOP|CBRS_BORDER_BOTTOM|CBRS_BORDER_LEFT|CBRS_BORDER_RIGHT
			| CBRS_TOOLTIPS | CBRS_FLYBY);
		ShowControlBar(&t_color,TRUE,FALSE);
		t_color.LoadToolBar(IDR_TOOLBAR1);

		for(i=0;i<16;i++)
		t_color.SetButtonStyle(i,TBBS_CHECKGROUP);

		t_draw.Create(this,WS_CHILD|WS_VISIBLE|CBRS_TOP|
			CBRS_BORDER_TOP|CBRS_BORDER_BOTTOM|CBRS_BORDER_LEFT|CBRS_BORDER_RIGHT
			| CBRS_TOOLTIPS | CBRS_FLYBY);
		ShowControlBar(&t_draw,TRUE,FALSE);
		t_draw.LoadToolBar(IDR_TOOLBAR2);

		for(i=0;i<9;i++)
		t_draw.SetButtonStyle(i,TBBS_CHECKGROUP);

		t_pstyle.Create(this,WS_CHILD|WS_VISIBLE|CBRS_TOP|
			CBRS_BORDER_TOP|CBRS_BORDER_BOTTOM|CBRS_BORDER_LEFT|CBRS_BORDER_RIGHT
			| CBRS_TOOLTIPS | CBRS_FLYBY);
		ShowControlBar(&t_pstyle,TRUE,FALSE);
		t_pstyle.LoadToolBar(IDR_TOOLBAR4);

		for(i=0;i<4;i++)
		t_pstyle.SetButtonStyle(i,TBBS_CHECKGROUP);



		init_default();

		visible_Wbar=visible_Cbar=visible_Dbar=visible_PSbar=1;
				
		st_bar.Create(this);		

		t_width.EnableDocking(CBRS_ALIGN_ANY);
		t_width.SetWindowText("Width");

		t_color.EnableDocking(CBRS_ALIGN_ANY);
		t_color.SetWindowText("Color");
		
		t_draw.EnableDocking(CBRS_ALIGN_ANY);
		t_draw.SetWindowText("Draw");

		t_pstyle.EnableDocking(CBRS_ALIGN_ANY);
		t_pstyle.SetWindowText("PenStyle");


		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&t_width,AFX_IDW_DOCKBAR_TOP);
		DockControlBar(&t_color,AFX_IDW_DOCKBAR_BOTTOM);
		DockControlBar(&t_draw,AFX_IDW_DOCKBAR_LEFT);
		DockControlBar(&t_pstyle,AFX_IDW_DOCKBAR_RIGHT);

		
		return 0;
	}

	
	
	void line_draw()
	{
		flag=0;
		ReleaseCapture();
		modelist.draw_mode='L'; //line drawing mode
		HCURSOR mycursor;
		mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);
		SetCursor(mycursor);
		SetCapture();
		flag2=0;
	}

	void freehand()
	{
		flag=0;
		ReleaseCapture();
		modelist.draw_mode='F'; //Freehand drawing mode
		HCURSOR mycursor;
		mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR2);
		SetCursor(mycursor);
		SetCapture();
		flag2=0;

	}

	void circle_draw()
	{
		flag=0;
		ReleaseCapture();
		modelist.draw_mode='C'; //Circle drawing mode
		HCURSOR mycursor;
		mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);
		SetCursor(mycursor);
		SetCapture();
		flag2=0;
	}

	void rectangle_draw()
	{
		flag=0;
		ReleaseCapture();
		modelist.draw_mode='R'; //Rectangle Drawing mode
		HCURSOR mycursor;
		mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);
		SetCursor(mycursor);
		SetCapture();
		flag2=0;
	}

	void polygon_draw()
	{
		flag=0;
		ReleaseCapture();
		modelist.draw_mode='P'; //Polygon Drawing mode
		HCURSOR mycursor;
		mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);
		SetCursor(mycursor);
		SetCapture();
		flag2=0;
	}

	void floodfill_draw()
	{
		flag=0;
		modelist.draw_mode='D'; //Floodfill
		flag2=0;
	}



	void OnLButtonDown(UINT u,CPoint pt)
	{
		
		if(flag==0)
			startpoint=betweenpt=endpoint=pt;

		if(modelist.draw_mode=='P' || modelist.draw_mode=='p')
		flag=1;

		if(modelist.draw_mode=='D' || modelist.draw_mode=='d' )
		{
			CClientDC d(this);
			int ptcolor;
			ptcolor=d.GetPixel(pt);
			
			myfloodfill(pt.x,pt.y,ptcolor,modelist.color,&d);
		}

		if(toupper(modelist.draw_mode=='K' ))
		{
			CClientDC d(this);
			modelist.color=d.GetPixel(pt);
		}





		
		
			
		
		SetCapture();
	}

	void OnMouseMove(UINT u,CPoint pt)
	{
		
		CPen mypen;
		CClientDC d(this);
		CPoint temp;
		CRect myrect;
		GetClientRect(myrect);
		if(pt.x>750 || pt.x<50 || pt.y>470 || pt.y<50) 
		{
			if(u!=MK_LBUTTON)
			{
				ReleaseCapture();
				flag2=0;
			}
			return;
		}
		else
		{
			if(flag2==0)
			{
				if(toupper(modelist.draw_mode)=='L' ||toupper(modelist.draw_mode)=='C' ||toupper(modelist.draw_mode)=='R' ||toupper(modelist.draw_mode)=='P')
				{
					HCURSOR mycursor;
					mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);
					SetCursor(mycursor);
					SetCapture();
				}

				if(toupper(modelist.draw_mode)=='F')
				{
					HCURSOR mycursor;
					mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR2);
					SetCursor(mycursor);
					SetCapture();
				}

				if(toupper(modelist.draw_mode)=='K')
				{
					HCURSOR mycursor;
					mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR4);
					SetCursor(mycursor);
					SetCapture();
				}
	

				if(toupper(modelist.draw_mode)=='E')
				{
					HCURSOR mycursor;
					mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR3);
					SetCursor(mycursor);
					SetCapture();
				}



				flag2=1;
			}
		}

				

	

		mypen.CreatePen(modelist.pen_style,modelist.pen_width,modelist.color);
		
		
		d.SelectObject(&mypen);
		d.SelectStockObject(NULL_BRUSH);
		
		
			
		switch(modelist.draw_mode)
			{
			case 'L':
			case 'l':
							
				d.SetROP2(R2_NOTXORPEN);

				if(u==(MK_LBUTTON | MK_SHIFT))//Draw a Horizontal or Vertical line if Shift key is down
				{
					if(abs(pt.y-startpoint.y)>abs(pt.x-startpoint.x))
						pt.x=startpoint.x;
					else
						pt.y=startpoint.y;

					d.MoveTo(startpoint);
					d.LineTo(endpoint);

					d.MoveTo(startpoint);
					d.LineTo(pt);
	
					endpoint=pt;
				}

				
				if(u==MK_LBUTTON)
				{
				d.MoveTo(startpoint);
				d.LineTo(endpoint);

				d.MoveTo(startpoint);
				d.LineTo(pt);

				endpoint=pt;
				}
				break;

			case 'F':
			case 'f': 
			case 'E':
			case 'e':
				
				if(toupper(modelist.draw_mode)=='E')
				{
					mypen.DeleteObject();
					mypen.CreatePen(PS_SOLID,8,RGB(255,255,255));
					d.SelectObject(&mypen);

				}
		
		

				if(u==MK_LBUTTON)
				{
				d.SetROP2(R2_COPYPEN);
				
				d.MoveTo(startpoint);
				d.LineTo(pt);

				startpoint=pt;
				}
				break;

			case 'C':
			case 'c':
				
				d.SetROP2(R2_NOTXORPEN);
				temp=pt;
				if(u==(MK_LBUTTON | MK_SHIFT)) //Force A Circle if Shift Key is Down
				{
					if(abs(pt.x-startpoint.x)>abs(pt.y-startpoint.y))
						temp.x=startpoint.x+pt.y-startpoint.y;
										
					else
						temp.y=startpoint.y+pt.x-startpoint.x;
								
				d.Ellipse(startpoint.x,startpoint.y,endpoint.x,endpoint.y);
				d.Ellipse(startpoint.x,startpoint.y,temp.x,temp.y);
				endpoint=temp;
				}

				
				if(u==MK_LBUTTON)
				{
				d.Ellipse(startpoint.x,startpoint.y,endpoint.x,endpoint.y);
				d.Ellipse(startpoint.x,startpoint.y,temp.x,temp.y);
				endpoint=pt;
				}
				break;	

			case 'R':
			case'r':
				
				d.SetROP2(R2_NOTXORPEN);

				temp=pt;
				if(u==(MK_LBUTTON | MK_SHIFT))  //Force a Square if Shift key is down
				{
					if(abs(pt.x-startpoint.x)>abs(pt.y-startpoint.y))
						temp.x=startpoint.x+pt.y-startpoint.y;
										
					else
						temp.y=startpoint.y+pt.x-startpoint.x;
								
				

				
				d.Rectangle(startpoint.x,startpoint.y,endpoint.x,endpoint.y);
				d.Rectangle(startpoint.x,startpoint.y,temp.x,temp.y);
				endpoint=temp;
				}

				if(u==MK_LBUTTON)
				{
					d.Rectangle(startpoint.x,startpoint.y,endpoint.x,endpoint.y);
					d.Rectangle(startpoint.x,startpoint.y,temp.x,temp.y);
					endpoint=temp;
				}
				
				break;

			case 'p':
			case 'P':
				
				if(u==MK_LBUTTON)
				{
					d.SetROP2(R2_NOTXORPEN);
					d.MoveTo(betweenpt);
					d.LineTo(endpoint);

					d.MoveTo(betweenpt);
					d.LineTo(pt);

					endpoint=pt;
				}

				break;
				
				

			}

			
	}

	void OnPaint()
	{
		CPaintDC d(this);
		d.Rectangle(40,40,760,480);
			
	}
	
	void myfloodfill(int x,int y,int oldvalue,int newvalue,CDC *p)
	{
		if(p->GetPixel(x,y)==unsigned int (oldvalue))
		{
			p->SetPixel(x,y,newvalue);
			myfloodfill(x,y-1,oldvalue,newvalue,p);
			myfloodfill(x,y+1,oldvalue,newvalue,p);
			myfloodfill(x-1,y,oldvalue,newvalue,p);
			myfloodfill(x+1,y,oldvalue,newvalue,p);
		}
			
	}
	
	void OnLButtonUp(UINT u,CPoint pt)
	{
		CPen mypen;
		CClientDC d(this);
		
		mypen.CreatePen(modelist.pen_style,modelist.pen_width,modelist.color);

		d.SelectObject(&mypen);
		d.SelectStockObject(NULL_BRUSH);
		flag2=0;

		
		/* Draw the final desired drawing in the pen color selected*/
		switch(modelist.draw_mode)
			{
			case 'L':
			case 'l': 
				d.SetROP2(R2_COPYPEN);
								

				d.MoveTo(startpoint);
				d.LineTo(endpoint);
				
				
				break;

			case 'c':
			case'C':
				d.SetROP2(R2_COPYPEN);
				d.Ellipse(startpoint.x,startpoint.y,endpoint.x,endpoint.y);
				break;

			case'R':
			case'r':
				d.SetROP2(R2_COPYPEN);
				d.Rectangle(startpoint.x,startpoint.y,endpoint.x,endpoint.y);
				break;
			
			case 'P':
			case'p':
				d.SetROP2(R2_COPYPEN);
				d.MoveTo(betweenpt);
				d.LineTo(endpoint);

				if(flag==1)
					betweenpt=endpoint;
				
				break;

			}
		
		ReleaseCapture(); //release the capture established in the OnLButtonDown event
		
	}

	void OnLButtonDblClk(UINT u,CPoint pt)
	{
		CClientDC d(this);
		CPen mypen;

		mypen.CreatePen(modelist.pen_style,modelist.pen_width,modelist.color);

		d.SelectObject(&mypen);
		d.SelectStockObject(NULL_BRUSH);
		
		if(flag==1)
		{
			d.SetROP2(R2_COPYPEN);
			d.MoveTo(betweenpt);
			d.LineTo(startpoint);
			flag=0;
		}
		ReleaseCapture();
	}

	void myLoadtoolbar(int id)
	{
		switch(id)
		{
		case 122:
			check1=!check1;
			break;
		
		case 123:
			check2=!check2;
			break;
		
		case 124:
			check3=!check3;
			break;
		
		case 125:
			check4=!check4;
			break;
		}
		
		if(check1==1)
		{
			ShowControlBar(&t_draw,TRUE,FALSE);		
			visible_Dbar=1;
		}
		else
		{
			if(visible_Dbar==1)
				ShowControlBar(&t_draw,FALSE,FALSE);
		}

		if(check2==1)
		{
			ShowControlBar(&t_pstyle,TRUE,FALSE);		
			visible_PSbar=1;
		}

		else
		{
			if(visible_PSbar==1)
				ShowControlBar(&t_pstyle,FALSE,FALSE);
		}

		
		
		
		
		if(check3==1)
		{
			ShowControlBar(&t_color,TRUE,FALSE);		
			visible_Cbar=1;
		}
		else
		{
			if(visible_Cbar==1)
				ShowControlBar(&t_color,FALSE,FALSE);
		}

		
		if(check4==1)
		{
			ShowControlBar(&t_width,TRUE,FALSE);		
			visible_Wbar=1;
		}

		else
		{
			if(visible_Wbar==1)
				ShowControlBar(&t_width,FALSE,FALSE);
		}
	}
	void setcheckmark(CCmdUI *item)
	{
		if(item->m_nID==122)
			item->SetCheck(check1);
		if(item->m_nID==123)
		{
			item->SetCheck(check2);
			if(modelist.pen_width!=1)
				item->Enable(0);
			else
				item->Enable(1);
		}
		if(item->m_nID==124)
			item->SetCheck(check3);
		if(item->m_nID==125)
			item->SetCheck(check4);
	}

	
	void select_width()
	{
		
		dialog_PenWidth d1(IDD_DIALOG1);	
		d1.DoModal();
	}

	void extra_color()
	{
		CColorDialog cd;
		if(cd.DoModal()==IDOK)
			modelist.color=cd.GetColor();
	}

	void erase_draw()
	{
		ReleaseCapture();
		modelist.draw_mode='E';
		HCURSOR mycursor;
		mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR3);
		SetCursor(mycursor);
		SetCapture();
	}

	void pickcolor_draw()
	{
		ReleaseCapture();
		modelist.draw_mode='K';
		HCURSOR mycursor;
		mycursor=AfxGetApp()->LoadCursor(IDC_CURSOR4);
		SetCursor(mycursor);
		SetCapture();
	}




	
	void init_default()
	{
		modelist.draw_mode='F' ;          //Freehand drawing mode
		modelist.pen_style=PS_SOLID; //Solid pen
		modelist.pen_width=1;               //width = 1 pixel wide  
		modelist.color=RGB(0,0,0);        //Black Color
	}

	void select_width2(int id)
	{
		if(id!=130)
		{
			ShowControlBar(&t_pstyle,FALSE,FALSE);
			visible_PSbar=0;
			check2=0;

		}
		else
		{
			ShowControlBar(&t_pstyle,TRUE,FALSE);
			visible_PSbar=1;
			check2=1;
		}
	

		
		switch(id)
		{
		case 130:
			modelist.pen_width=1;
			break;
		case 131:
			modelist.pen_width=2;
			break;
		case 132:
			modelist.pen_width=3;
			break;
		case 133:
			modelist.pen_width=4;
			break;
		case 134:
			modelist.pen_width=5;
			break;
		}
	}

	void select_palette_color(int id)
	{
		switch(id)
		{
		case 200:
			modelist.color=RGB(0,0,0);
			break;
		case 201:
			modelist.color=RGB(255,255,255);
			break;
		case 202:
			modelist.color=RGB(192,192,192);
			break;
		case 203:
			modelist.color=RGB(128,128,128);
			break;
		case 204:
			modelist.color=RGB(128,128,0);
			break;
		case 205:
			modelist.color=RGB(128,0,0);
			break;
		case 206:
			modelist.color=RGB(0,0,128);
			break;
		case 207:
			modelist.color=RGB(128,0,128);
			break;
		case 208:
			modelist.color=RGB(255,0,0);
			break;
		case 209:
			modelist.color=RGB(255,255,0);
			break;
		case 210:
			modelist.color=RGB(0,0,255);
			break;
		case 211:
			modelist.color=RGB(255,0,255);
			break;
		case 212:
			modelist.color=RGB(0,128,128);
			break;
		case 213:
			modelist.color=RGB(0,128,0);
			break;
		case 214:
			modelist.color=RGB(0,255,0);
			break;
		case 215:
			modelist.color=RGB(0,255,255);
			break;
		}
	}


	void select_pen_style(int id)
	{
		switch(id)
		{
		case 135:
			modelist.pen_style=PS_DASH;
			break;
		case 136:
			modelist.pen_style=PS_DOT;
			break;
		case 137:
			modelist.pen_style=PS_DASHDOT;
			break;
		case 138: 
			modelist.pen_style=PS_SOLID;
			break;
	
		}
	}



	


		
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(myframe,CFrameWnd)
ON_WM_CREATE()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_LBUTTONDBLCLK()
ON_COMMAND(112,line_draw)
ON_COMMAND(113,freehand)
ON_WM_PAINT()
ON_COMMAND(114,circle_draw)
ON_COMMAND(115,rectangle_draw)
ON_COMMAND(116,polygon_draw)
ON_COMMAND(118,floodfill_draw)
ON_COMMAND(128,erase_draw)
ON_COMMAND(127,pickcolor_draw)
ON_COMMAND(119,select_width)
ON_COMMAND(121,extra_color)
ON_COMMAND_RANGE(122,125,myLoadtoolbar)
ON_UPDATE_COMMAND_UI_RANGE(122,125,setcheckmark)
ON_COMMAND_RANGE(130,134,select_width2)
ON_COMMAND_RANGE(200,215,select_palette_color)
ON_COMMAND_RANGE(135,138,select_pen_style)
END_MESSAGE_MAP()

class myapp:public CWinApp
{
public:
	int InitInstance()
	{
		myframe *p;
		p=new myframe;
		p->ShowWindow(3);
		m_pMainWnd=p;

		return 1;
	}
};

myapp a;

		
	