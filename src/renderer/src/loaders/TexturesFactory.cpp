#include "renderer/loaders/TexturesFactory.hpp"

#include "renderer/Texture.hpp"
#include "renderer/CubeTexture.hpp"
#include "renderer/TextureTiling.hpp"
#include "renderer/TextureFilteringMode.hpp"

#include "loaders/formats/LoadTga.hpp"

#include "utils/Assert.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> TexturesFactory::load2dTextureFromFile(std::string_view _filePath)
{
	s32 width, height, bpp;
	std::unique_ptr<char[]> tgaBuffer(loadTga(_filePath.data(), &width, &height, &bpp));

	ASSERTM(tgaBuffer, "Can not load texture from file: {}", _filePath);
	ASSERTM(width > 0 && height > 0, "Invalid texture size");
	ASSERTM(bpp == 24 || bpp == 32, "Unsupported bpp");
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
	texture->setMagnificationFilteringMode(TextureFilteringMode::Linear);
	texture->setMinificationFilteringMode(TextureFilteringMode::LinearMipmapLinear);
	return texture;
}

//-----------------------------------------------------------------------------

std::unique_ptr<CubeTexture> TexturesFactory::loadCubeTextureFromFile(std::string_view _filePath)
{
	s32 width, height, bpp;
	std::unique_ptr<char[]> tgaBuffer(loadTga(_filePath.data(), &width, &height, &bpp));

	ASSERTM(tgaBuffer, "Can not load texture from file: {}", _filePath);
	ASSERTM(width > 0 && height > 0, "Invalid texture size");
	ASSERTM(bpp == 24 || bpp == 32, "Unsupported bpp");
	if (!tgaBuffer || width <= 0 || height <= 0 || !(bpp == 24 || bpp == 32))
	{
		return nullptr;
	}

	ASSERTM(width / 4 == height / 3, "Cube texture has invalid width or/and height");

	CubeTexture::InitData texInitData;
	texInitData.data	= std::move(tgaBuffer);
	texInitData.width	= static_cast<u32>(width);
	texInitData.height	= static_cast<u32>(height);
	texInitData.bpp		= static_cast<u32>(bpp);

	auto texture = std::make_unique<CubeTexture>(texInitData);
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

	return createFrameTexture(texInitData);
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

	return createFrameTexture(texInitData);
}

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> TexturesFactory::createFrameTexture(const Texture::InitData& _textureInitData)
{
	auto texture = std::make_unique<Texture>(_textureInitData);
	texture->setTiling(TextureTiling::ClampToEdge);
	texture->setMagnificationFilteringMode(TextureFilteringMode::Nearest);
	texture->setMinificationFilteringMode(TextureFilteringMode::Nearest);
	return texture;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
