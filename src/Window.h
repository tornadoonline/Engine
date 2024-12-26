#pragma once

/* <editor-fold desc="MIT License">

Copyright(c) 2021 Robert Osfield

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

</editor-fold> */

//#include <QVulkanInstance>
#include <QWindow>

#include <vsg/app/Window.h>

#include <KeyboardMap.h>
#include <Viewer.h>

namespace Engine
{

    class Window : public QWindow
    {
    public:
        Window(QScreen* targetScreen = nullptr);
        Window(QWindow* parent);
        Window(vsg::ref_ptr<vsg::WindowTraits> in_traits, QScreen* targetScreen = nullptr);
        Window(vsg::ref_ptr<vsg::WindowTraits> in_traits, QWindow* parent);
        Window(vsg::ref_ptr<Engine::Viewer> in_viewer, vsg::ref_ptr<vsg::WindowTraits> in_traits, QScreen* targetScreen = nullptr);
        Window(vsg::ref_ptr<Engine::Viewer> in_viewer, vsg::ref_ptr<vsg::WindowTraits> in_traits, QWindow* parent);

        virtual ~Window();

        vsg::ref_ptr<vsg::WindowTraits> traits;
        vsg::ref_ptr<Engine::Viewer> viewer;

        vsg::ref_ptr<vsg::Window> windowAdapter;
        vsg::ref_ptr<KeyboardMap> keyboardMap;

        operator vsg::ref_ptr<vsg::Window>() { return windowAdapter; }

        /// Initialize the Vulkan integration using VulkanSceneGraph VkInstance/VkSurface support
        virtual void initializeWindow();

    protected:
        void cleanup();

        bool event(QEvent* e) override;

        void exposeEvent(QExposeEvent*) override;
        void hideEvent(QHideEvent* ev) override;

        void keyPressEvent(QKeyEvent*) override;
        void keyReleaseEvent(QKeyEvent*) override;
        void mouseMoveEvent(QMouseEvent*) override;
        void mousePressEvent(QMouseEvent*) override;
        void mouseReleaseEvent(QMouseEvent*) override;
        void resizeEvent(QResizeEvent*) override;
        void wheelEvent(QWheelEvent*) override;

        /// convert Qt's window coordinate into Vulkan/VSG ones by scaling by the devicePixelRatio()
        template<typename T>
        int32_t convert_coord(T c) const { return static_cast<int32_t>(std::round(static_cast<qreal>(c) * devicePixelRatio())); }

        std::pair<vsg::ButtonMask, uint32_t> convertMouseButtons(QMouseEvent* e) const;
        std::pair<int32_t, int32_t> convertMousePosition(QMouseEvent* e) const;

    private:
        bool _initialized = false;
    };

} // namespace Engine

EVSG_type_name(Engine::Window);
