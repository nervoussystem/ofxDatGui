/*
    Copyright (C) 2015 Stephen Braitsch [http://braitsch.io]

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#pragma once
#include "ofxDatGuiButton.h"

class ofxDatGuiHeader : public ofxDatGuiButton {

    public:

        ofxDatGuiHeader(string label, bool draggable = true) : ofxDatGuiButton(label)
        {
            mDraggable = draggable;
            setTheme(ofxDatGuiComponent::theme.get());
        }
    
        void setTheme(ofxDatGuiTheme* theme)
        {
            setComponentStyle(theme);
            mLabel.width = mStyle.width;
            mStyle.stripe.visible = false;
            mStyle.height = mStyle.height * .8;
            setLabelAlignment(ofxDatGuiAlignment::CENTER);
			mLabel.color = theme->color.header.text;
			mStyle.height = theme->layout.header.height;
			mFont = theme->layout.header.font.ptr;
        }
    
        void setDraggable(bool draggable)
        {
            mDraggable = draggable;
        }
    
        bool getDraggable()
        {
            return mDraggable;
        }
    
        ofPoint getDragOffset()
        {
            return mDragOffset;
        }
		void draw()
		{
			if (mVisible) {
				// anything that extends ofxDatGuiButton has the same rollover effect //
				ofPushStyle();
				if (mStyle.border.visible) drawBorder();
				ofFill();
				/*if (mFocused && mMouseDown) {
					ofSetColor(mStyle.color.onMouseDown, mStyle.opacity);
				}
				else if (mMouseOver) {
					ofSetColor(mStyle.color.onMouseOver, mStyle.opacity);
				}
				else {*/
					ofSetColor(mStyle.color.background, mStyle.opacity);
				//}
				ofDrawRectangle(x, y, mStyle.width, mStyle.height);
				drawLabel();
				if (mStyle.stripe.visible) drawStripe();
				ofPopStyle();
			}
		}
	
    
    protected:

        void onMouseEnter(ofPoint m)
        {
        // disable hover state if we're not draggable //
            if (mDraggable) ofxDatGuiComponent::onMouseEnter(m);
        }
    
        void onMousePress(ofPoint m)
        {
            mDragOffset = ofPoint(m.x-this->x,m.y-this->y);
            ofxDatGuiComponent::onMousePress(m);
        }
    
        void onMouseRelease(ofPoint m)
        {
            mDragOffset = m;
            ofxDatGuiComponent::onFocusLost();
            ofxDatGuiComponent::onMouseRelease(m);
        }
    
    // allow panel to be dragged around //
        void onFocusLost() {}
    // force header label to always be centered //
        void setLabelAlignment(ofxDatGuiAlignment align)
        {
          //  ofxDatGuiComponent::setLabelAlignment(ofxDatGuiAlignment::CENTER);
        }
    
    private:
        bool mDraggable;
        ofPoint mDragOffset;

};

class ofxDatGuiFooter : public ofxDatGuiButton {

    public:
    
        ofxDatGuiFooter() : ofxDatGuiButton("collapse controls")
        {
            mGuiCollapsed = false;
            mLabelCollapsed = "expand controls";
            mLabelExpanded = "collapse controls";
            setTheme(ofxDatGuiComponent::theme.get());
        }
    
        void setTheme(ofxDatGuiTheme* theme)
        {
            setComponentStyle(theme);
            mLabel.width = mStyle.width;
            mStyle.stripe.visible = false;
            mStyle.height = mStyle.height * .8;
            setLabelAlignment(ofxDatGuiAlignment::CENTER);
        }
    
        void setLabelWhenExpanded(string label)
        {
            mLabelExpanded = label;
            if (!mGuiCollapsed) setLabel(mLabelExpanded);
        }
    
        void setLabelWhenCollapsed(string label)
        {
            mLabelCollapsed = label;
            if (mGuiCollapsed) setLabel(mLabelCollapsed);
        }
    
        void setY(int y)
        {
            this->y = y;
        }
    
    protected:
    
        void onMouseRelease(ofPoint m)
        {
            mGuiCollapsed = !mGuiCollapsed;
            ofxDatGuiComponent::onMouseRelease(m);
        // dispatch event out to main application //
            ofxDatGuiInternalEvent e(ofxDatGuiEventType::GUI_TOGGLED, mIndex);
            internalEventCallback(e);
            if (!mGuiCollapsed){
                setLabel(mLabelExpanded);
            }   else{
                setLabel(mLabelCollapsed);
            }
        }
    
    // force footer label to always be centered //
        void setLabelAlignment(ofxDatGuiAlignment align)
        {
            ofxDatGuiComponent::setLabelAlignment(ofxDatGuiAlignment::CENTER);
        }
    
    private:
        bool mGuiCollapsed;
        string mLabelExpanded;
        string mLabelCollapsed;
    
};
