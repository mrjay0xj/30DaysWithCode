//+------------------------------------------------------------------+
#property strict

string winName      = "MyWindow";
string titleName    = "MyWindowTitle";
string closeName    = "MyWindowClose";
string shadowName   = "MyWindowShadow";

int winWidth  = 350;
int winHeight = 250;

int posX, posY;
bool dragging = false;
int dragOffsetX, dragOffsetY;

//+------------------------------------------------------------------+
int OnInit()
{
   CreateWindow();
   CenterWindow();
   return(INIT_SUCCEEDED);
}
//+------------------------------------------------------------------+
void CreateWindow()
{
   // --- Shadow
   ObjectCreate(0, shadowName, OBJ_RECTANGLE_LABEL, 0, 0, 0);
   ObjectSetInteger(0, shadowName, OBJPROP_BGCOLOR, clrGray);
   ObjectSetInteger(0, shadowName, OBJPROP_XSIZE, winWidth);
   ObjectSetInteger(0, shadowName, OBJPROP_YSIZE, winHeight);
   ObjectSetInteger(0, shadowName, OBJPROP_CORNER, CORNER_LEFT_UPPER);

   // --- Main window
   ObjectCreate(0, winName, OBJ_RECTANGLE_LABEL, 0, 0, 0);
   ObjectSetInteger(0, winName, OBJPROP_BGCOLOR, clrWhite);
   ObjectSetInteger(0, winName, OBJPROP_BORDER_TYPE, BORDER_FLAT);
   ObjectSetInteger(0, winName, OBJPROP_XSIZE, winWidth);
   ObjectSetInteger(0, winName, OBJPROP_YSIZE, winHeight);
   ObjectSetInteger(0, winName, OBJPROP_CORNER, CORNER_LEFT_UPPER);

   // --- Title bar
   ObjectCreate(0, titleName, OBJ_RECTANGLE_LABEL, 0, 0, 0);
   ObjectSetInteger(0, titleName, OBJPROP_BGCOLOR, clrDodgerBlue);
   ObjectSetInteger(0, titleName, OBJPROP_XSIZE, winWidth);
   ObjectSetInteger(0, titleName, OBJPROP_YSIZE, 30);
   ObjectSetInteger(0, titleName, OBJPROP_CORNER, CORNER_LEFT_UPPER);

   // --- Close button
   ObjectCreate(0, closeName, OBJ_BUTTON, 0, 0, 0);
   ObjectSetString(0, closeName, OBJPROP_TEXT, "X");
   ObjectSetInteger(0, closeName, OBJPROP_XSIZE, 30);
   ObjectSetInteger(0, closeName, OBJPROP_YSIZE, 30);
   ObjectSetInteger(0, closeName, OBJPROP_CORNER, CORNER_LEFT_UPPER);
}
//+------------------------------------------------------------------+
void CenterWindow()
{
   int chartW = (int)ChartGetInteger(0, CHART_WIDTH_IN_PIXELS);
   int chartH = (int)ChartGetInteger(0, CHART_HEIGHT_IN_PIXELS);

   posX = (chartW - winWidth) / 2;
   posY = (chartH - winHeight) / 2;

   UpdatePositions();
}
//+------------------------------------------------------------------+
void UpdatePositions()
{
   // Shadow slightly offset
   ObjectSetInteger(0, shadowName, OBJPROP_XDISTANCE, posX + 5);
   ObjectSetInteger(0, shadowName, OBJPROP_YDISTANCE, posY + 5);

   // Main window
   ObjectSetInteger(0, winName, OBJPROP_XDISTANCE, posX);
   ObjectSetInteger(0, winName, OBJPROP_YDISTANCE, posY);

   // Title bar
   ObjectSetInteger(0, titleName, OBJPROP_XDISTANCE, posX);
   ObjectSetInteger(0, titleName, OBJPROP_YDISTANCE, posY);

   // Close button (top right)
   ObjectSetInteger(0, closeName, OBJPROP_XDISTANCE, posX + winWidth - 30);
   ObjectSetInteger(0, closeName, OBJPROP_YDISTANCE, posY);
}
//+------------------------------------------------------------------+
void OnChartEvent(const int id,
                  const long &lparam,
                  const double &dparam,
                  const string &sparam)
{
   // --- Resize handling
   if(id == CHARTEVENT_CHART_CHANGE)
      CenterWindow();

   // --- Close button click
   if(id == CHARTEVENT_OBJECT_CLICK && sparam == closeName)
      DeleteWindow();

   // --- Drag start
   if(id == CHARTEVENT_OBJECT_CLICK && sparam == titleName)
   {
      dragging = true;
      dragOffsetX = (int)lparam - posX;
      dragOffsetY = (int)dparam - posY;
   }

   // --- Drag move
   if(id == CHARTEVENT_MOUSE_MOVE && dragging)
   {
      posX = (int)lparam - dragOffsetX;
      posY = (int)dparam - dragOffsetY;
      UpdatePositions();
   }

   // --- Drag release
   if(id == CHARTEVENT_CLICK)
      dragging = false;
}
//+------------------------------------------------------------------+
void DeleteWindow()
{
   ObjectDelete(0, winName);
   ObjectDelete(0, titleName);
   ObjectDelete(0, closeName);
   ObjectDelete(0, shadowName);
}
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
{
   DeleteWindow();
}
