#include "factories/TexturesFactory.hpp"
#include "factories/formats/LoadTga.hpp"

#include "renderer/CubeTexture.hpp"
#include "renderer/TextureTiling.hpp"
#include "renderer/TextureFilteringMode.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Texture> TexturesFactory::load2dTextureFromFile(std::string_view _filePath)
{
	jl::s32 width, height, bpp;
	std::unique_ptr<char[]> tgaBuffer(loadTga(_filePath.data(), &width, &height, &bpp));

	ASSERTM(tgaBuffer, "Can not load texture from file: {}", _filePath);
	ASSERTM(width > 0 && height > 0, "Invalid texture size");
	ASSERTM(bpp == 24 || bpp == 32, "Unsupported bpp");
	if (!tgaBuffer || width <= 0 || height <= 0 || !(bpp == 24 || bpp == 32))
	{
		return nullptr;
	}

	jl::Texture::InitData texInitData;
	texInitData.data			= std::move(tgaBuffer);
	texInitData.width			= static_cast<jl::u32>(width);
	texInitData.height			= static_cast<jl::u32>(height);
	texInitData.format			= bpp == 32 ? jl::Texture::Format::Rgba : jl::Texture::Format::Rgb;
	texInitData.fragmentType	= jl::Texture::FragmentType::UnsignedByte;

	auto texture = std::make_unique<jl::Texture>(texInitData);
	texture->setMagnificationFilteringMode(jl::TextureFilteringMode::Linear);
	texture->setMinificationFilteringMode(jl::TextureFilteringMode::LinearMipmapLinear);
	return texture;
}

//-----------------------------------------------------------------------------

std::unique_ptr<jl::CubeTexture> TexturesFactory::loadCubeTextureFromFile(std::string_view _filePath)
{
	jl::s32 width, height, bpp;
	std::unique_ptr<char[]> tgaBuffer(loadTga(_filePath.data(), &width, &height, &bpp));

	ASSERTM(tgaBuffer, "Can not load texture from file: {}", _filePath);
	ASSERTM(width > 0 && height > 0, "Invalid texture size");
	ASSERTM(bpp == 24 || bpp == 32, "Unsupported bpp");
	if (!tgaBuffer || width <= 0 || height <= 0 || !(bpp == 24 || bpp == 32))
	{
		return nullptr;
	}

	ASSERTM(width / 4 == height / 3, "Cube texture has invalid width or/and height");

	jl::CubeTexture::InitData texInitData;
	texInitData.data	= std::move(tgaBuffer);
	texInitData.width	= static_cast<jl::u32>(width);
	texInitData.height	= static_cast<jl::u32>(height);
	texInitData.bpp		= static_cast<jl::u32>(bpp);

	auto texture = std::make_unique<jl::CubeTexture>(texInitData);
	texture->setMagnificationFilteringMode(jl::TextureFilteringMode::Linear);
	texture->setMinificationFilteringMode(jl::TextureFilteringMode::LinearMipmapLinear);
	return texture;
}

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Texture> TexturesFactory::createFrameColorTexture(jl::u32 _width, jl::u32 _height)
{
	jl::Texture::InitData texInitData;
	texInitData.data			= nullptr;
	texInitData.width			= _width;
	texInitData.height			= _height;
	texInitData.format			= jl::Texture::Format::Rgba;
	texInitData.fragmentType	= jl::Texture::FragmentType::UnsignedByte;

	return createFrameTexture(texInitData);
}

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Texture> TexturesFactory::createFrameDepthTexture(jl::u32 _width, jl::u32 _height)
{
	jl::Texture::InitData texInitData;
	texInitData.data			= nullptr;
	texInitData.width			= _width;
	texInitData.height			= _height;
	texInitData.format			= jl::Texture::Format::DepthComponent;
	texInitData.fragmentType	= jl::Texture::FragmentType::UnsignedInt;

	return createFrameTexture(texInitData);
}

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Texture> TexturesFactory::createFrameTexture(const jl::Texture::InitData& _textureInitData)
{
	auto texture = std::make_unique<jl::Texture>(_textureInitData);
	texture->setTiling(jl::TextureTiling::ClampToEdge);
	texture->setMagnificationFilteringMode(jl::TextureFilteringMode::Nearest);
	texture->setMinificationFilteringMode(jl::TextureFilteringMode::Nearest);
	return texture;
}

//-----------------------------------------------------------------------------
