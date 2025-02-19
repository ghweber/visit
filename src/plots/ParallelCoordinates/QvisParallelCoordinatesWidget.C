// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.
#include <QvisParallelCoordinatesWidget.h>
#include <math.h>
#include <qdrawutil.h>
#include <QPainter>
#include <QPixmap>
#include <QPen>
#include <QPaintEvent>
#include <vectortypes.h>
#include <visitstream.h>

static double sampleYs[8][3] = {
    { 0.21, 0.55, 0.85 },
    { 0.32, 0.81, 0.61 },
    { 0.17, 0.77, 0.65 },
    { 0.93, 0.11, 0.57 },
    { 0.62, 0.13, 0.33 },
    { 0.71, 0.42, 0.26 },
    { 0.88, 0.56, 0.31 },
    { 0.48, 0.54, 0.63 }
};


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::QvisParallelCoordinatesWidget
//
// Purpose: 
//   Constructor for the QvisParallelCoordinatesWidget class.
//
// Arguments:
//   parent : The parent of this widget.
//   name   : This widget's name.
//
// Note: This is intended to emulate the style of the QvisScatterWidget used
//       in the Scatter plot, which came first.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//    Cyrus Harrison, Mon Jul 21 08:33:47 PDT 2008
//    Initial Qt4 Port. 
//
// ****************************************************************************

QvisParallelCoordinatesWidget::QvisParallelCoordinatesWidget(QWidget *parent) 
: QWidget(parent)
{
    axisCount = 2;
    namedRightAxis = false;

    axisTitles.clear();
    axisTitles.push_back(std::string("var1"));

    pixmap      = NULL;
    pixmapDirty = true;
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::~QvisParallelCoordinatesWidget
//
// Purpose: 
//   Destructor for the QvisParallelCoordinatesWidget class.
//
// Note: This is intended to emulate the style of the QvisScatterWidget used
//       in the Scatter plot, which came first.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

QvisParallelCoordinatesWidget::~QvisParallelCoordinatesWidget()
{
    deleteBackingPixmap();
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::sizeHint
//
// Purpose: 
//   Returns the widget's preferred size.
//
// Returns:    The widget's preferred size.
//
// Note: This is intended to emulate the style of the QvisScatterWidget used
//       in the Scatter plot, which came first.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

QSize
QvisParallelCoordinatesWidget::sizeHint() const
{
    return QSize(250,250);
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::sizePolicy
//
// Purpose: 
//   Returns the widget's size policy.
//
// Returns:    The widget's size policy.
//
// Note: This is intended to emulate the style of the QvisScatterWidget used
//       in the Scatter plot, which came first.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

QSizePolicy
QvisParallelCoordinatesWidget::sizePolicy() const
{
    return QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::deleteBackingPixmap
//
// Purpose: 
//   Deletes the backing pixmap.
//
// Note: This is intended to emulate the style of the QvisScatterWidget used
//       in the Scatter plot, which came first.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
QvisParallelCoordinatesWidget::deleteBackingPixmap()
{
    if (pixmap != NULL)
    {
        delete pixmap;
        pixmap = NULL;
    }
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::setNumberOfAxes
//
// Purpose: Sets the number of axes to be drawn in the scene.
//
// Arguments:
//   axisCount_ : Number of axes to draw in scene
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
QvisParallelCoordinatesWidget::setNumberOfAxes(int axisCount_)
{
    axisCount = axisCount_;
    pixmapDirty = true;
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::setAxisTitles
//
// Purpose: Sets the titles (names) to be drawn at the bottoms of the axes when
//          the axes are drawn.
//
// Arguments:
//   axisTitles_: Titles (names) of axes to draw in scene
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//    Cyrus Harrison, Mon Jul 21 08:33:47 PDT 2008
//    Initial Qt4 Port. 
//
// ****************************************************************************

void
QvisParallelCoordinatesWidget::setAxisTitles(const stringVector &titles)
{
    axisTitles = titles;
    pixmapDirty = true;
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::redrawAllAxes
//
// Purpose: Redraws the scene with current number of axes and axis titles.
//
// Arguments:
//   rightAxisNamed : If true, right axis and its title will be drawn in the
//                    foreground color, as it would be for all the other axes.
//                    If false, right axis will be drawn in a different color
//                    and its title will be drawn as "?".
//
// Note: This is intended to emulate the style of the QvisScatterWidget used
//       in the Scatter plot, which came first.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
QvisParallelCoordinatesWidget::redrawAllAxes(bool rightAxisNamed)
{
    namedRightAxis = rightAxisNamed;
    
    pixmapDirty = true;
    update();
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::redrawScene
//
// Purpose: 
//   Redraws the scene.
//
// Arguments:
//   painter : The painter to use to redraw the scene.
//
// Note: This is intended to emulate the style of the QvisScatterWidget used
//       in the Scatter plot, which came first.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//    Cyrus Harrison, Mon Jul 21 08:33:47 PDT 2008
//    Initial Qt4 Port. 
//
// ****************************************************************************

void
QvisParallelCoordinatesWidget::redrawScene(QPainter *painter)
{
    double sceneWidth = (double)width();
    double sceneHeight = (double)height();
    double leftAxisX = sceneWidth * AXIS_LEFT_MARGIN;
    double axisSpacing = (sceneWidth*(1.0-AXIS_LEFT_MARGIN-AXIS_RIGHT_MARGIN)) /
        (double)(axisCount-1);
    double tickSpacing = (sceneHeight*(1.0-AXIS_BOTTOM_MARGIN-AXIS_TOP_MARGIN)) /
        (double)(TICKS_PER_AXIS+1);
    
    QBrush backgroundBrush(QColor(255,255,255));
    qDrawShadePanel(painter,
        0, 0, width(), height(), palette(), true, 2, &backgroundBrush);
        
    axisBottomY = (int)(sceneHeight*(1.0-AXIS_BOTTOM_MARGIN) + 0.5);
    axisTopY    = (int)(sceneHeight*AXIS_TOP_MARGIN + 0.5);
    
    axesXPos.clear();
    
    for (int axisNum = 0; axisNum < axisCount; axisNum++)
    {
        axesXPos.push_back((int)(leftAxisX + (double)axisNum*axisSpacing + 0.5));
    }
    
    ticksYPos.clear();
    
    for (int tickNum = 1; tickNum <= TICKS_PER_AXIS; tickNum++)
    {
        ticksYPos.push_back((int)(axisTopY + (double)tickNum*tickSpacing + 0.5));
    }
    
    double axisLen = (double)(axisBottomY - axisTopY);
    double dashAndGapLen = axisLen / ((double)DASHES_PER_AXIS - DASH_GAP_FRACTION);
    double dashTopYPos = (double)axisTopY;
    int dashLen = (int)(dashAndGapLen * (1.0-DASH_GAP_FRACTION));
        
    dashesTopYPos.clear(); dashesBotYPos.clear();
    
    for (int dashNum = 0; dashNum < DASHES_PER_AXIS; dashNum++)
    {
        dashesTopYPos.push_back((int)dashTopYPos);
        dashesBotYPos.push_back((int)dashTopYPos + dashLen);
        
        dashTopYPos += dashAndGapLen;
    }
    
    dashesBotYPos[DASHES_PER_AXIS-1] = axisBottomY;

    drawDataCurves(painter);
    drawAxes(painter);
    drawAxisTitles(painter);
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::drawAxes
//
// Purpose: Draws currently selected coordinate axes with tick marks.  If new
//          axis is about to be selected, draws it on the far right in red.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
QvisParallelCoordinatesWidget::drawAxes(QPainter *painter)
{
    int axisNum, axisX;

    painter->setPen(QPen(QColor(0,0,0), AXIS_AND_TICK_WIDTH));

    for (axisNum = 0; axisNum < axisCount; axisNum++)
    {
        axisX = axesXPos[axisNum];

        if ((!namedRightAxis && (axisNum == axisCount-1)) ||
            (axisNum >= (int)axisTitles.size()))
        {
            for (size_t dashNum = 0; dashNum < dashesTopYPos.size(); dashNum++)
            {
                painter->drawLine(axisX, dashesTopYPos[dashNum],
                                  axisX, dashesBotYPos[dashNum]);
            }
        }
        else
        {
            painter->drawLine(axisX, axisBottomY, axisX, axisTopY);
            
            for (size_t tickNum = 0; tickNum < ticksYPos.size(); tickNum++)
            {
                painter->drawLine(axisX-TICK_HALF_LENGTH, ticksYPos[tickNum],
                                  axisX+TICK_HALF_LENGTH, ticksYPos[tickNum]);
            }
        }
    }
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::drawAxisTitles
//
// Purpose: Draws titles (variable names) of currently selected coordinate
//          axes.  If new axis is about to be selected, draws "???" as its title.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
QvisParallelCoordinatesWidget::drawAxisTitles(QPainter *painter)
{
    int charSpacing = (fontMetrics().height() * 2) / 3;
    int maxTitleChars = (int)((double)height()*AXIS_BOTTOM_MARGIN) / charSpacing;
    int axisNum, axisX, titleCharCount, charNum, charXPos, charYPos;
    size_t slashIndex;
    std::string axisTitle, titleChar;

    painter->setPen(QPen(QColor(0,80,255), AXIS_AND_TICK_WIDTH));

    for (axisNum = 0; axisNum < axisCount; axisNum++)
    {
        if ((!namedRightAxis && (axisNum == axisCount-1)) ||
            (axisNum >= (int)axisTitles.size()))
        {
            axisTitle = std::string("?");
            titleCharCount = 1;
        }
        else
        {
            axisTitle = axisTitles[axisNum];
            if ((slashIndex = axisTitle.find_first_of("/")) != std::string::npos)
                axisTitle = axisTitle.substr(slashIndex+1);
            titleCharCount =
            ((int)axisTitle.length() > maxTitleChars) ? maxTitleChars : (int) axisTitle.length();
        }
        
        axisX = axesXPos[axisNum];
        
        for (charNum = 0; charNum < titleCharCount; charNum++)
        {
            titleChar = axisTitle.substr(charNum, 1);
            charXPos = axisX - fontMetrics().horizontalAdvance(QChar(*(axisTitle.c_str())))/2;
            charYPos = (charNum+1)*charSpacing + axisBottomY;

            painter->drawText(charXPos, charYPos, QString(titleChar.c_str()));
        }
    }
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::drawDataCurves
//
// Purpose: Draws simulated data curves between currently selected coordinate
//          axes.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
QvisParallelCoordinatesWidget::drawDataCurves(QPainter *painter)
{
    double axisHeight = (double)height() * (1.0-AXIS_BOTTOM_MARGIN-AXIS_TOP_MARGIN);
    int axisNum, segNum;
    int leftAxisX, leftAxisY, rightAxisX, rightAxisY;

    painter->setPen(QPen(QColor(128,128,128), 1));

    for (axisNum = 0; axisNum < axisCount-1 && axisNum < 8; axisNum++)
    {
        leftAxisX = axesXPos[axisNum]; rightAxisX = axesXPos[axisNum+1];
        
        for (segNum = 0; segNum < 3; segNum++)
        {
            leftAxisY  = (int)(sampleYs[axisNum  ][segNum]*axisHeight + axisTopY);
            rightAxisY = (int)(sampleYs[axisNum+1][segNum]*axisHeight + axisTopY);

            painter->drawLine(leftAxisX, leftAxisY, rightAxisX, rightAxisY);
        }
    }
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::paintEvent
//
// Purpose: 
//   This method is called when the widget needs to be repainted.
//
// Arguments:
//   e : The paint event to process.
//
// Note: This is intended to emulate the style of the QvisScatterWidget used
//       in the Scatter plot, which came first.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//    Cyrus Harrison, Mon Jul 21 08:33:47 PDT 2008
//    Initial Qt4 Port. 
//
// ****************************************************************************

void
QvisParallelCoordinatesWidget::paintEvent(QPaintEvent *e)
{
    bool clipByRegion = true;

    // Draw the scene into the backing pixmap.
    bool needsPaint = pixmapDirty;

    if (pixmap == NULL)
    {
        needsPaint = true;
        pixmap = new QPixmap(width(), height());
    }

    if (needsPaint)
    {
        QPainter pixpaint(pixmap);
        redrawScene(&pixpaint);
        clipByRegion = false;
        pixmapDirty = false;
    }

    // Blit the pixmap to the screen.
    QPainter paint(this);
    if (clipByRegion && !e->region().isEmpty())
        paint.setClipRegion(e->region());
    paint.drawPixmap(QPoint(0,0), *pixmap);
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::resizeEvent
//
// Purpose: 
//   This method is called when the widget needs to be resized.
//
// Arguments:
//   e : The resize event.
//
// Note: This is intended to emulate the style of the QvisScatterWidget used
//       in the Scatter plot, which came first.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
QvisParallelCoordinatesWidget::resizeEvent(QResizeEvent *e)
{
    deleteBackingPixmap();
    
    pixmapDirty = true;
    update();
}


//
// Qt slot functions
//

// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::show
//
// Purpose: 
//   This is a Qt slot function that is called when the widget is shown.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
QvisParallelCoordinatesWidget::show()
{
    QWidget::show();
    // Maybe future animation code here.
}


// ****************************************************************************
// Method: QvisParallelCoordinatesWidget::hide
//
// Purpose: 
//   This is a Qt slot function that is called when the widget is hidden.
//
// Programmer: Mark Blair
// Creation:   Wed Jun 14 18:54:00 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
QvisParallelCoordinatesWidget::hide()
{
    QWidget::hide();
    // Maybe future animation code here.
}
