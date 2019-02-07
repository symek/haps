
//
// This source file is part of appleseed.
// Visit https://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2014-2018 Hans Hoogenboom, Esteban Tovagliari, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

// appleseed.renderer headers.
#include "renderer/api/rendering.h"

// Standard headers.
#include <memory>

// Forward declarations.
namespace foundation    { class Logger; }

namespace HAPS {

class HoudiniTileCallback : public renderer::TileCallbackBase 
{
public:
    static HoudiniTileCallback* createCallback(IMG_TileDevice* );

    HoudiniTileCallback(IMG_TileDevice* device) : m_device(device) {};

    // The factory always return the same tile callback instance.
    // Prevent this instance from being destroyed by doing nothing here.
    void release() override {};
    void on_tiled_frame_begin(const renderer::Frame* frame) override;
    void on_tile_end(const renderer::Frame* , const size_t , const size_t ) override; 
    void on_progressive_frame_update(const renderer::Frame* ) override;
    void send_tile(const renderer::Frame* , const size_t, const size_t, const size_t, const size_t) ;
    void send_tile_flipped(const renderer::Frame* , const size_t, const size_t, const size_t, const size_t) ;
private:
    IMG_TileDevice* m_device;
    std::mutex       m_mutex;
    std::unique_ptr<float[]> 
                    m_buffer;
    size_t m_buffer_size = 0;
};

class MPlayTileCallbackFactory
  : public renderer::ITileCallbackFactory
{
  public:
    MPlayTileCallbackFactory(IMG_TileDevice* device);

    void release() override;

    renderer::ITileCallback* create() override;

  private:
    std::unique_ptr<renderer::ITileCallback> m_callback;
};

}   // namespace HAPS
