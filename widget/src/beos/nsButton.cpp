/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or 
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "nsButton.h"
#include "nsToolkit.h"
#include "nsColor.h"
#include "nsGUIEvent.h"
#include "nsString.h"

#include "nsILookAndFeel.h"
#include "nsWidgetsCID.h"
#include "nsIComponentManager.h"

#include "nsIDeviceContext.h"
#include "nsIFontMetrics.h"

static NS_DEFINE_IID(kLookAndFeelCID, NS_LOOKANDFEEL_CID);
static NS_DEFINE_IID(kILookAndFeelIID, NS_ILOOKANDFEEL_IID);


//-------------------------------------------------------------------------
//
// nsButton constructor
//
//-------------------------------------------------------------------------
nsButton::nsButton() : nsWindow() , nsIButton()
{
}

//-------------------------------------------------------------------------
//
// nsButton destructor
//
//-------------------------------------------------------------------------
nsButton::~nsButton()
{
}

/**
 * Implement the standard QueryInterface for NS_IWIDGET_IID and NS_ISUPPORTS_IID
 * @modify gpk 8/4/98
 * @param aIID The name of the class implementing the method
 * @param _classiiddef The name of the #define symbol that defines the IID
 * for the class (e.g. NS_ISUPPORTS_IID)
 * 
*/ 
nsresult nsButton::QueryInterface(const nsIID& aIID, void** aInstancePtr)
{
    if (NULL == aInstancePtr) {
        return NS_ERROR_NULL_POINTER;
    }

    static NS_DEFINE_IID(kIButton, NS_IBUTTON_IID);
    if (aIID.Equals(kIButton)) {
        *aInstancePtr = (void*) ((nsIButton*)this);
        NS_ADDREF_THIS();
        return NS_OK;
    }

    return nsWindow::QueryInterface(aIID,aInstancePtr);
}


//-------------------------------------------------------------------------
//
// Set this button label
//
//-------------------------------------------------------------------------
NS_METHOD nsButton::SetLabel(const nsString& aText)
{
  mLabel = aText;
  if(NULL == mView) {
    return NS_ERROR_FAILURE;
  }
  if(mButton)
  {
    if(mButton->Looper())
    	mButton->LockLooper();

    mButton->SetLabel(NS_LossyConvertUCS2toASCII(aText).get());
    
    if(mButton->Looper())
    	mButton->UnlockLooper();
  }
  return NS_OK;
}

//-------------------------------------------------------------------------
//
// Get this button label
//
//-------------------------------------------------------------------------
NS_METHOD nsButton::GetLabel(nsString& aBuffer)
{
  aBuffer = mLabel;
  return NS_OK;
}

//-------------------------------------------------------------------------
//
// move, paint, resizes message - ignore
//
//-------------------------------------------------------------------------
PRBool nsButton::OnMove(PRInt32, PRInt32)
{
  return PR_FALSE;
}

PRBool nsButton::OnPaint(nsRect &r)
{
  //printf("** nsButton::OnPaint **\n");
  return PR_FALSE;
}

PRBool nsButton::OnResize(nsRect &aWindowRect)
{
    return PR_FALSE;
}

/**
 * Renders the Button for Printing
 *
 **/
NS_METHOD nsButton::Paint(nsIRenderingContext& aRenderingContext,
                          const nsRect& aDirtyRect)
{
  float appUnits;
  float devUnits;
  float scale;
  nsIDeviceContext * context;
  aRenderingContext.GetDeviceContext(context);

  context->GetCanonicalPixelScale(scale);
  context->GetAppUnitsToDevUnits(devUnits);
  context->GetDevUnitsToAppUnits(appUnits);

  nsRect rect;
  GetBoundsAppUnits(rect, appUnits);
  aRenderingContext.SetColor(NS_RGB(0,0,0));

  nscolor bgColor  = NS_RGB(255,255,255);
  nscolor fgColor  = NS_RGB(0,0,0);
  nscolor hltColor = NS_RGB(240,240,240);
  nscolor sdwColor = NS_RGB(128,128,128);

  nsILookAndFeel * lookAndFeel;
  if (NS_OK == nsComponentManager::CreateInstance(kLookAndFeelCID, nsnull, kILookAndFeelIID, (void**)&lookAndFeel)) {
   lookAndFeel->GetColor(nsILookAndFeel::eColor_WidgetBackground,  bgColor);
   lookAndFeel->GetColor(nsILookAndFeel::eColor_WidgetForeground,  fgColor);
   lookAndFeel->GetColor(nsILookAndFeel::eColor_Widget3DShadow,    sdwColor);
   lookAndFeel->GetColor(nsILookAndFeel::eColor_Widget3DHighlight, hltColor);
  }

  aRenderingContext.SetColor(bgColor);
  aRenderingContext.FillRect(rect);

  /*aRenderingContext.SetColor(bgColor);
  for (int i=0;i<int(scale);i++) {
    aRenderingContext.DrawRect(rect);
    rect.x      += 3; 
    rect.y      += 3;
    rect.width  -= 6; 
    rect.height -= 6;
  }*/

  nscoord onePixel  = nscoord(scale);
  nscoord twoPixels = nscoord(scale*2);

  rect.x      += onePixel; 
  rect.y      += onePixel;
  rect.width  -= twoPixels; 
  rect.height -= twoPixels;

  nscoord right     = rect.x+rect.width;
  nscoord bottom    = rect.y+rect.height;


  // Draw Left & Top
  aRenderingContext.SetColor(NS_RGB(225,225,225));
  DrawScaledLine(aRenderingContext, rect.x, rect.y, right, rect.y, scale, appUnits, PR_TRUE); // top
  DrawScaledLine(aRenderingContext, rect.x, rect.y, rect.x, bottom, scale, appUnits, PR_FALSE); // left

  //DrawScaledLine(aRenderingContext, rect.x+onePixel, rect.y+onePixel, right-onePixel, rect.y+onePixel, scale, appUnits, PR_TRUE); // top + 1
  //DrawScaledLine(aRenderingContext, rect.x+onePixel, rect.y+onePixel, rect.x+onePixel, bottom-onePixel, scale, appUnits, PR_FALSE); // left + 1

  // Draw Right & Bottom
  aRenderingContext.SetColor(NS_RGB(128,128,128));
  DrawScaledLine(aRenderingContext, right, rect.y+onePixel, right, bottom, scale, appUnits, PR_FALSE); // right 
  DrawScaledLine(aRenderingContext, rect.x+onePixel, bottom, right, bottom, scale, appUnits, PR_TRUE); // bottom

  //DrawScaledLine(aRenderingContext, right-onePixel, rect.y+twoPixels, right-onePixel, bottom, scale, appUnits, PR_FALSE); // right + 1
  //DrawScaledLine(aRenderingContext, rect.x+twoPixels, bottom-onePixel, right, bottom-onePixel, scale, appUnits, PR_TRUE); // bottom + 1

  aRenderingContext.SetFont(*mFont);

  nscoord textWidth;
  nscoord textHeight;
  aRenderingContext.GetWidth(mLabel, textWidth);

  nsIFontMetrics* metrics;
  context->GetMetricsFor(*mFont, metrics);
  metrics->GetMaxAscent(textHeight);

  nscoord x = ((rect.width  - textWidth) / 2)  + rect.x;
  nscoord y = ((rect.height - textHeight) / 2) + rect.y;
  aRenderingContext.DrawString(mLabel, x, y);


  NS_RELEASE(context);
  return NS_OK;
}

BView *nsButton::CreateBeOSView()
{
	return mButton = new nsButtonBeOS(this, BRect(0, 0, 0, 0), "", "");
}

//-------------------------------------------------------------------------
// Sub-class of BeOS Button
//-------------------------------------------------------------------------
nsButtonBeOS::nsButtonBeOS( nsIWidget *aWidgetWindow, BRect aFrame, 
    const char *aName, const char *aLabel, uint32 aResizingMode, uint32 aFlags )
  : BButton( aFrame, aName, aLabel, new BMessage('clik'), aResizingMode, aFlags ),
    nsIWidgetStore( aWidgetWindow )
{
}

void nsButtonBeOS::AttachedToWindow()
{
	SetTarget(this);
}

void nsButtonBeOS::MessageReceived(BMessage *msg)
{
	switch(msg->what)
	{
		case 'clik' :
			{
			nsWindow	*w = (nsWindow *)GetMozillaWidget();
			nsToolkit	*t;
			if(w && (t = w->GetToolkit()) != 0)
			{
				uint32	args[5];
				args[0] = NS_MOUSE_LEFT_CLICK;
				args[1] = (uint32)0;
				args[2] = (uint32)0;
				args[3] = 1;
				args[4] = modifiers();
				MethodInfo *info = new MethodInfo(w, w, nsWindow::BTNCLICK, 5, args);
				t->CallMethodAsync(info);
				NS_RELEASE(t);
			}
			}
			break;

		default :
			BButton::MessageReceived(msg);
	}
}

