// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <stdlib.h>
#include <math.h>
#include "vtkRubberBandMapper2D.h"

#include <vtkActor2D.h>
#include <vtkCellArray.h>
#include <vtkCoordinate.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkProperty2D.h>
#include <vtkScalarsToColors.h>
#include <vtkViewport.h>
#include <vtkWindow.h>

#if defined(_WIN32)
#  include <windows.h>
#endif
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QLine>
#if defined(HAVE_XLIB)
#  include <QtX11Extras/QX11Info>
#  include <X11/Intrinsic.h>
#endif

struct vtkRubberBandMapper2DPrivate
{
    QWidget *widget;
    int      bestRenderer;
    QLabel  *overlay;

    vtkRubberBandMapper2DPrivate()
    {
        widget = 0;
        bestRenderer = -1;
        overlay = 0;
    }

    vtkRubberBandMapper2DPrivate(const vtkRubberBandMapper2DPrivate &obj)
    {
        widget = obj.widget;
        bestRenderer = obj.bestRenderer;
        overlay = 0;
    }

    ~vtkRubberBandMapper2DPrivate()
    {
        ReleaseGraphicsResources();
    }

    void operator = (const vtkRubberBandMapper2DPrivate &obj)
    {
        widget = obj.widget;
        bestRenderer = obj.bestRenderer;
        overlay = 0;
    }

    // Delete the overlay with deleteLater so we don't clobber a widget
    // that Qt assumes is still valid during a mouse event.
    void ReleaseGraphicsResources()
    {
        if(overlay != 0)
            overlay->deleteLater();
        overlay = 0;
    }

    int SelectBestRenderer()
    {
        if(bestRenderer != -1)
            return bestRenderer;

#if defined(__APPLE__) || defined(_WIN32)
        bestRenderer = 2;
#elif defined(HAVE_XLIB)
        bestRenderer = 1;
#if 0
// X is not creating the Qt overlay as transparent. Disable for now.
        // See if we're displaying to Apple X11. If so we want Qt renderer.
        int nExt = 0, appleDisplay = 0;
        char **ext = XListExtensions(QX11Info::display(), &nExt);
        for(int e = 0; e < nExt; ++e)
        {
            if(strcmp(ext[e], "Apple-DRI") == 0 ||
               strcmp(ext[e], "Apple-WM") == 0)
            {
                appleDisplay++;
            }
        }
        XFreeExtensionList(ext);
        if(appleDisplay == 2)
            bestRenderer = 2;
#endif
#else
        bestRenderer = 2;
#endif

        return bestRenderer;
    }
};

// ***************************************************************************
//  Modifications:
//    Kathleen Bonnell, Wed Mar  6 15:14:29 PST 2002
//    Replace 'New' method with Macro to match VTK 4.0 API.
// ***************************************************************************

vtkStandardNewMacro(vtkRubberBandMapper2D);

// ****************************************************************************
// Method: vtkRubberBandMapper2D::vtkRubberBandMapper2D
//
// Purpose:
//   Constructor.
//
// Programmer: Brad Whitlock
// Creation:   Mon Mar 13 10:04:25 PDT 2006
//
// Modifications:
//
// ****************************************************************************

vtkRubberBandMapper2D::vtkRubberBandMapper2D() : vtkPolyDataMapper2D()
{
    privateInstance = new vtkRubberBandMapper2DPrivate;
}

// ****************************************************************************
// Method: vtkRubberBandMapper2D::~vtkRubberBandMapper2D
//
// Purpose:
//   Destructor.
//
// Programmer: Brad Whitlock
// Creation:   Mon Mar 13 10:04:03 PDT 2006
//
// Modifications:
//
// ****************************************************************************

vtkRubberBandMapper2D::~vtkRubberBandMapper2D()
{
    if(privateInstance != 0)
    {
        delete privateInstance;
        privateInstance = 0;
    }
}

// ****************************************************************************
// Method: vtkRubberBandMapper2D::ReleaseGraphicsResources
//
// Purpose:
//   Releases the mapper's graphics resources.
//
// Arguments:
//   win : The vtkWindow for which resources are released.
//
// Note:       The APPLE implementation frees a transparent overlay rendering
//             window.
//
// Programmer: Brad Whitlock
// Creation:   Mon Mar 13 10:01:08 PDT 2006
//
// Modifications:
//
// ****************************************************************************

void
vtkRubberBandMapper2D::ReleaseGraphicsResources(vtkWindow *win)
{
    privateInstance->ReleaseGraphicsResources();

    // Call the superclass's ReleaseGraphicsResources method.
    vtkPolyDataMapper2D::ReleaseGraphicsResources(win);
}

// ****************************************************************************
// Method: vtkRubberBandMapper2D::SetWidget
//
// Purpose:
//   Set the widget that we want to draw over.
//
// Arguments:
//   w : The widget that we want to draw over.
//
// Programmer: Brad Whitlock
// Creation:   Fri Oct 14 14:27:04 PDT 2011
//
// Modifications:
//
// ****************************************************************************

void
vtkRubberBandMapper2D::SetWidget(QWidget *w)
{
    privateInstance->widget = w;
}

// ****************************************************************************
// Method: vtkRubberBandMapper2D::RenderOverlay
//
// Purpose:
//   Render the polydata as an "overlay".
//
// Arguments:
//   viewport : The viewport into which we're rendering.
//   actor    : The actor.
//
// Programmer: Brad Whitlock
// Creation:   Fri Oct 14 14:19:53 PDT 2011
//
// Modifications:
//
// ****************************************************************************

void
vtkRubberBandMapper2D::RenderOverlay(vtkViewport* viewport, vtkActor2D* actor)
{
    if(privateInstance->widget != 0)
    {
        switch(privateInstance->SelectBestRenderer())
        {
        case 1:
            RenderOverlay_X11(viewport, actor);
            break;
        case 2:
            RenderOverlay_Qt(viewport, actor);
            break;
        }
    }
}

// ***************************************************************************
//
// X11 coding and macros
//
// ***************************************************************************

void
vtkRubberBandMapper2D::RenderOverlay_X11(vtkViewport* viewport, vtkActor2D* actor)
{
#if defined(HAVE_XLIB)
#define STORE_POINT(P, X, Y) P.x = short(X); P.y = short(Y);

#define SET_FOREGROUND_D(rgba) \
      aColor.red = (unsigned short) (rgba[0] * 65535.0); \
      aColor.green = (unsigned short) (rgba[1] * 65535.0); \
      aColor.blue = (unsigned short) (rgba[2] * 65535.0); \
      XAllocColor(displayId, attr.colormap, &aColor); \
      XSetForeground(displayId, gc, aColor.pixel); \
      XSetFillStyle(displayId, gc, FillSolid);

#define SET_FOREGROUND(rgba) \
      aColor.red = (unsigned short) (rgba[0] * 256); \
      aColor.green = (unsigned short) (rgba[1] * 256); \
      aColor.blue = (unsigned short) (rgba[2] * 256); \
      XAllocColor(displayId, attr.colormap, &aColor); \
      XSetForeground(displayId, gc, aColor.pixel);

#define DRAW_POLYGON(points, npts) XFillPolygon(displayId, drawable, \
      gc, points, npts, Complex, CoordModeOrigin);

#define RESIZE_POINT_ARRAY(points, npts, currSize) \
      if (npts > currSize) \
      { \
      delete [] points; \
      points = new XPoint [npts]; \
      currSize = npts; \
      }

#define DRAW_XOR_LINE(x1, y1, x2, y2) \
      XDrawLine(displayId, drawable, xorGC, x1, y1, x2, y2);

#define FLUSH_AND_SYNC() XFlush(displayId); XSync(displayId, False); \
      XFreeGC(displayId, gc);

#define BEGIN_POLYLINE(X,Y)

#define END_POLYLINE()

#define CLEAN_UP() delete [] points;

    XColor aColor;
    XPoint *points = new XPoint [1024];

    Display* displayId = (Display*) QX11Info::display();
    Window windowId = (Window) privateInstance->widget->winId();

    Screen *screen = XDefaultScreenOfDisplay(displayId);
    int screenN = XScreenNumberOfScreen(screen);
    unsigned long black = BlackPixel(displayId, screenN);
    unsigned long white = WhitePixel(displayId, screenN);
    XGCValues xgcvalues;
    xgcvalues.foreground = black ^ white;
    xgcvalues.background = 0;
    xgcvalues.function = GXxor;
    GC gc = XCreateGC(displayId, windowId, GCForeground | GCBackground | GCFunction,
                      &xgcvalues);
    GC xorGC = XCreateGC(displayId, windowId, GCForeground | GCBackground | GCFunction,
                      &xgcvalues);

    // Get the drawable to draw into
    Drawable drawable = (Drawable) windowId;
    if (!drawable) vtkErrorMacro(<<"Window returned NULL drawable!");

    // Set up the forground color
    XWindowAttributes attr;
    XGetWindowAttributes(displayId,windowId,&attr);

    // Set the line color
    double* actorColor = actor->GetProperty()->GetColor();
    SET_FOREGROUND_D(actorColor);

#include <vtkRubberBandMapper2D_body.C>
#endif
}

// ***************************************************************************
//
// Qt coding and macros
//
//  Modifications:
//    Kathleen Biagas, Mon Jun 11 15:48:10 MST 2012
//    Remove ifdef preventing this method from bein used on _WIN32
//
// ***************************************************************************

void
vtkRubberBandMapper2D::RenderOverlay_Qt(vtkViewport* viewport, vtkActor2D* actor)
{
#define STORE_POINT(P, X, Y) cerr << "STORE_POINT macro for Qt." << endl;

#define SET_FOREGROUND_D(rgba) \
    painter.setPen(QColor(int(255.*rgba[0]), int(255.*rgba[1]), int(255.*rgba[2])));

#define SET_FOREGROUND(rgba) \
    painter.setPen(QColor(int(255.*rgba[0]), int(255.*rgba[1]), int(255.*rgba[2])));

#define DRAW_POLYGON(points, npts) \
    cerr << "DRAW_POLYGON macro for Qt." << endl;

#define RESIZE_POINT_ARRAY(points, npts, currSize) \
    currSize = currSize; \
    cerr << "RESIZE_POINT_ARRAY macro for Qt." << endl;

#define DRAW_XOR_LINE(x1, y1, x2, y2) \
    painter.drawLine(QLine(x1, y1, x2, y2));

#define FLUSH_AND_SYNC() \
    privateInstance->overlay->setPixmap(pixmap);

#define CLEAN_UP()

#define BEGIN_POLYLINE(X, Y)

#define END_POLYLINE()

    int x,y,w,h;
    QPoint tl(privateInstance->widget->mapToGlobal(QPoint(0,0)));

    x = tl.x();
    y = tl.y();
    w = privateInstance->widget->width();
    h = privateInstance->widget->height();

    QPixmap pixmap(w, h);
    pixmap.fill(Qt::transparent);

    //
    // Try and create the window if we've not yet created it.
    //
    if(privateInstance->overlay == 0)
    {
        privateInstance->overlay = new QLabel(0, Qt::FramelessWindowHint);
        privateInstance->overlay->setAttribute(Qt::WA_TranslucentBackground);
        // FIXME? We should need the following, but it triggers a Qt
        // bug and  strangely everything seems to work without it.
        //privateInstance->overlay->setAttribute(Qt::WA_TransparentForMouseEvents);
        privateInstance->overlay->setAutoFillBackground(false);
        privateInstance->overlay->setPixmap(pixmap);
    }

    privateInstance->overlay->setGeometry(x, y, w, h);
    privateInstance->overlay->show();

    // Clear the window so it's ready for us to draw.
    QPainter painter(&pixmap);

    // Set the line color
    double* actorColor = actor->GetProperty()->GetColor();
    SET_FOREGROUND_D(actorColor);

#include <vtkRubberBandMapper2D_body.C>
}
