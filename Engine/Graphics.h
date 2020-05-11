/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include <cassert>
#include "RectI.h"
#include "Surface.h"

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	void drawRectDim(int x, int y, int w, int h, Color c, bool fill);
	void drawRect(int x, int y, int x0, int y0, Color c, bool fill)
	{
		drawRectDim(x, y, x0 - x, y0 - y, c, fill);
	}
	void DrawSpriteSubstitute(int x, int y, Color substitute, const Surface& s, Color chroma)
	{
		DrawSpriteSubstitute(x, y, substitute, s.GetRect(), s, chroma);
	}
	void DrawSpriteSubstitute(int x, int y, Color substitute, const RectI& srcRect, const Surface& s, Color chroma)
	{
		DrawSpriteSubstitute(x, y, substitute, srcRect, GetScreenRect(), s, chroma);
	}
	void DrawSpriteSubstitute(int x, int y, Color substitute, RectI srcRect, const RectI& clip, const Surface& s, Color chroma)
	{
		assert(srcRect.left >= 0);
		assert(srcRect.right <= s.GetWidth());
		assert(srcRect.top >= 0);
		assert(srcRect.bottom <= s.GetHeight());
		if (x < clip.left)
		{
			srcRect.left += clip.left - x;
			x = clip.left;
		}
		if (y < clip.top)
		{
			srcRect.top += clip.top - y;
			y = clip.top;
		}
		if (x + srcRect.GetWidth() > clip.right)
		{
			srcRect.right -= x + srcRect.GetWidth() - clip.right;
		}
		if (y + srcRect.GetHeight() > clip.bottom)
		{
			srcRect.bottom -= y + srcRect.GetHeight() - clip.bottom;
		}
		for (int sy = srcRect.top; sy < srcRect.bottom; sy++)
		{
			for (int sx = srcRect.left; sx < srcRect.right; sx++)
			{
				const Color srcPixel = s.GetPixel(sx, sy);
				if (srcPixel != chroma)
				{
					// use substitute color instead of color from the surface (if not chroma)
					PutPixel(x + sx - srcRect.left, y + sy - srcRect.top, substitute);
				}
			}
		}
	}
	void Drawbox(int x, int y, int width, int height, int border, Color color, Color borderColor, bool fill)
	{
		assert(border > 0);
		assert(width > border * 2);
		assert(height > border * 2);

		for (int i = 0; i < border; ++i)
		{
			drawRectDim(x + i, y + i, width - i * 2, height - i * 2, borderColor, false);
		}
		if (fill)
		{
			drawRectDim(x + border, y + border, width - border * 2, height - border * 2, color, true);
		}
	}
	void FillScreen(int r, int g, int b)
	{
		for (int i = 0; i < ScreenWidth; i++)
			for (int j = 0; j < ScreenHeight; j++)
				PutPixel(i, j, r, g, b);
	}
	~Graphics();
	RectI Graphics::GetScreenRect()
	{
		return{ 0,ScreenWidth,0,ScreenHeight };
	}
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
};