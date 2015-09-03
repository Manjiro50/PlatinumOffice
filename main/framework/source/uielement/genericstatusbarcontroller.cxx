/**************************************************************
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *************************************************************/

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_framework.hxx"

#include <uielement/genericstatusbarcontroller.hxx>
#include <uielement/statusbarmerger.hxx>

#include <vos/mutex.hxx>
#include <vcl/svapp.hxx>
#include <vcl/status.hxx>
#include <vcl/image.hxx>
#include <toolkit/helper/vclunohelper.hxx>
#include <toolkit/helper/convert.hxx>

#include <com/sun/star/ui/ItemStyle.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/awt/ImageDrawMode.hpp>
#include <com/sun/star/graphic/GraphicType.hpp>

using ::rtl::OUString;

using namespace ::cppu;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::frame;

namespace framework
{

GenericStatusbarController::GenericStatusbarController(
    const Reference< XMultiServiceFactory >& rxServiceManager,
    const Reference< XFrame >& rxFrame,
    const Reference< ui::XStatusbarItem >& rxItem,
    AddonStatusbarItemData *pItemData )
    : svt::StatusbarController( rxServiceManager, rxFrame, OUString(), 0 )
    , m_bEnabled( sal_False )
    , m_bOwnerDraw( sal_False )
    , m_pItemData( pItemData )
    , m_xGraphic()
{
    m_xStatusbarItem = rxItem;
    if ( m_xStatusbarItem.is() )
    {
        m_aCommandURL = m_xStatusbarItem->getCommand();
        m_nID = m_xStatusbarItem->getItemId();
        m_bOwnerDraw = ( m_xStatusbarItem->getStyle() & ui::ItemStyle::OWNER_DRAW ) == ui::ItemStyle::OWNER_DRAW;
        if ( !m_bOwnerDraw && m_pItemData && m_pItemData->aLabel.getLength() )
            m_xStatusbarItem->setText( m_pItemData->aLabel );
    }
}

GenericStatusbarController::~GenericStatusbarController()
{
}

void SAL_CALL GenericStatusbarController::dispose()
throw ( RuntimeException )
{
    svt::StatusbarController::dispose();

    vos::OGuard aSolarMutexGuard( Application::GetSolarMutex() );
    m_pItemData = NULL;
    m_xGraphic.clear();
    m_xStatusbarItem.clear();

}

void SAL_CALL GenericStatusbarController::statusChanged(
    const FeatureStateEvent& rEvent)
throw ( RuntimeException )
{
    vos::OGuard aSolarMutexGuard( Application::GetSolarMutex() );

    if ( m_bDisposed || !m_xStatusbarItem.is() )
        return;

    m_bEnabled = rEvent.IsEnabled;

    rtl::OUString aStrValue;
    Reference< graphic::XGraphic > aGraphic;

    if ( rEvent.State >>= aStrValue )
    {
        if ( !m_bOwnerDraw )
            m_xStatusbarItem->setText( aStrValue );
        else
        {
            if ( aStrValue.getLength() )
            {
                m_xStatusbarItem->setQuickHelpText( aStrValue );
            }
        }
    }
    else if ( ( rEvent.State >>= aGraphic ) && m_bOwnerDraw )
    {
        m_xGraphic = aGraphic;
    }

    // when the status is updated, and the controller is responsible for
    // painting the statusbar item content, we must trigger a repaint
    if ( m_bOwnerDraw && m_xStatusbarItem->getVisible() )
    {
        m_xStatusbarItem->repaint();
    }
}

void SAL_CALL GenericStatusbarController::paint(
    const Reference< awt::XGraphics >& xGraphics,
    const awt::Rectangle& rOutputRectangle,
    ::sal_Int32 /*nStyle*/ )
throw ( RuntimeException )
{
    OSL_TRACE("framework::GenericStatusbarController::paint");
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    if ( !m_xStatusbarItem.is() || !xGraphics.is() )
        return;

    Reference< beans::XPropertySet > xGraphicProps( m_xGraphic, UNO_QUERY );

    if ( xGraphicProps.is() && m_xGraphic->getType() != graphic::GraphicType::EMPTY )
    {
        awt::Size aGraphicSize;
        xGraphicProps->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("SizePixel") ) ) >>= aGraphicSize;
        OSL_ENSURE( aGraphicSize.Height > 0 && aGraphicSize.Width > 0, "Empty status bar graphic!" );

        sal_Int32 nOffset = m_xStatusbarItem->getOffset( );
        awt::Point aPos;
        aPos.X = ( rOutputRectangle.Width + nOffset ) / 2 - aGraphicSize.Width / 2;
        aPos.Y = rOutputRectangle.Height / 2 - aGraphicSize.Height / 2;

        xGraphics->drawImage( rOutputRectangle.X + aPos.X,
                              rOutputRectangle.Y + aPos.Y,
                              aGraphicSize.Width,
                              aGraphicSize.Height,
                              m_bEnabled ? awt::ImageDrawMode::NONE : awt::ImageDrawMode::DISABLE,
                              m_xGraphic );
    }
    else
    {
        xGraphics->clear( rOutputRectangle );
    }
}


}