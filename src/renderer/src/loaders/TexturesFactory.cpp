#include "renderer/loaders/TexturesFactory.hpp"

#include "renderer/gl_primitives/Texture.hpp"
#include "renderer/gl_primitives/CubeTexture.hpp"
#include "renderer/gl_primitives/TextureTiling.hpp"

#include "loaders/formats/LoadTga.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> TexturesFactory::load2dTextureFromFile(std::string_view _filePath, TextureTiling _tiling)
{
	s32 width, height, bpp;
	std::unique_ptr<char[]> tgaBuffer(loadTga(_filePath.data(), &width, &height, &bpp));

	ASSERT(tgaBuffer, "Can not load texture from file: {}", _filePath);
	ASSERT(width > 0 && height > 0, "Invalid texture size");
	ASSERT(bpp == 24 || bpp == 32, "Unsupported bpp");
	if (!tgaBuffer || width <= 0 || height <= 0 || !(bpp == 24 || bpp == 32))
	{
		return nullptr;
	}

	Texture::InitData texInitData;
	texInitData.data			= std::move(tgaBuffer);
	texInitData.width			= static_cast<u32>(width);
	texInitData.height			= static_cast<u32>(height);
	texInitData.format			= bpp == 32 ? Texture::Format::Rgba : Texture::Format::Rgb;
	texInitData.fragmentType	= Texture::FragmentType::UnsignedByte;

	auto texture = std::make_unique<Texture>(texInitData);
	texture->setTiling(_tiling);
	texture->setMagnificationFilteringMode(TextureFilteringMode::Linear);
	texture->setMinificationFilteringMode(TextureFilteringMode::LinearMipmapLinear);
	return texture;
}

//-----------------------------------------------------------------------------

std::unique_ptr<CubeTexture> TexturesFactory::loadCubeTextureFromFile(std::string_view _filePath, TextureTiling _tiling)
{
	s32 width, height, bpp;
	std::unique_ptr<char[]> tgaBuffer(loadTga(_filePath.data(), &width, &height, &bpp));

	ASSERT(tgaBuffer, "Can not load texture from file: {}", _filePath);
	ASSERT(width > 0 && height > 0, "Invalid texture size");
	ASSERT(bpp == 24 || bpp == 32, "Unsupported bpp");
	if (!tgaBuffer || width <= 0 || height <= 0 || !(bpp == 24 || bpp == 32))
	{
		return nullptr;
	}

	ASSERT(width / 4 == height / 3, "Cube texture has invalid width or/and height");

	CubeTexture::InitData texInitData;
	texInitData.data			= std::move(tgaBuffer);
	texInitData.width			= static_cast<u32>(width);
	texInitData.height			= static_cast<u32>(height);

	auto texture = std::make_unique<CubeTexture>(texInitData);
	texture->setTiling(_tiling);
	texture->setMagnificationFilteringMode(TextureFilteringMode::Linear);
	texture->setMinificationFilteringMode(TextureFilteringMode::LinearMipmapLinear);
	return texture;
}

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> TexturesFactory::createFrameColorTexture(u32 _width, u32 _height)
{
	Texture::InitData texInitData;
	texInitData.data			= nullptr;
	texInitData.width			= _width;
	texInitData.height			= _height;
	texInitData.format			= Texture::Format::Rgba;
	texInitData.fragmentType	= Texture::FragmentType::UnsignedByte;

	auto texture = std::make_unique<Texture>(Texture::Format::Rgba, texInitData);
	texture->setTiling(TextureTiling::ClampToEdge);
	texture->setMagnificationFilteringMode(TextureFilteringMode::Nearest);
	texture->setMinificationFilteringMode(TextureFilteringMode::Nearest);
	return texture;
}

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> TexturesFactory::createFrameDepthTexture(u32 _width, u32 _height)
{
	Texture::InitData texInitData;
	texInitData.data			= nullptr;
	texInitData.width			= _width;
	texInitData.height			= _height;
	texInitData.format			= Texture::Format::DepthComponent;
	texInitData.fragmentType	= Texture::FragmentType::UnsignedInt;

	auto texture = std::make_unique<Texture>(Texture::Format::Rgba, texInitData);
	texture->setTiling(TextureTiling::ClampToEdge);
	texture->setMagnificationFilteringMode(TextureFilteringMode::Nearest);
	texture->setMinificationFilteringMode(TextureFilteringMode::Nearest);
	return texture;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
