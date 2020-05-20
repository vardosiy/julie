#include "renderer/Texture.hpp"
#include "renderer/TextureTiling.hpp"
#include "renderer/TextureFiltering.hpp"

#include "formats/LoadTga.hpp"

#include "utils/Utils.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> Texture::loadFromFile(std::string_view _filePath)
{
	int width, height, bpp;
	std::unique_ptr<char[]> tgaBuffer(loadTga(_filePath.data(), &width, &height, &bpp));

	ASSERTM(tgaBuffer, "Can not load texture from file: {}", _filePath);
	ASSERTM(width > 0 && height > 0, "Invalid texture size");
	ASSERTM(bpp == 24 || bpp == 32, "Unsupported bpp");
	if (!tgaBuffer || width <= 0 || height <= 0 || !(bpp == 24 || bpp == 32))
	{
		return nullptr;
	}

	const Format format = bpp == 32 ? Format::Rgba : Format::Rgb;

	Texture* texture = new Texture(tgaBuffer.get(), width, height, format, FragmentType::UnsignedByte);
	texture->setMagnificationFilteringMode(TextureFiltering::Linear);
	texture->setMinificationFilteringMode(TextureFiltering::LinearMipmapLinear);
	return std::unique_ptr<Texture>(texture);
}

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> Texture::createColorTexture(u32 _width, u32 _height)
{
	Texture* texture = new Texture(nullptr, _width, _height, Format::Rgba, FragmentType::UnsignedByte);
	texture->setTiling(TextureTiling::ClampToEdge);
	texture->setMagnificationFilteringMode(TextureFiltering::Nearest);
	texture->setMinificationFilteringMode(TextureFiltering::Nearest);
	return std::unique_ptr<Texture>(texture);
}

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> Texture::createDepthTexture(u32 _width, u32 _height)
{
	Texture* texture = new Texture(nullptr, _width, _height, Format::DepthComponent, FragmentType::UnsignedInt);
	texture->setTiling(TextureTiling::ClampToEdge);
	texture->setMagnificationFilteringMode(TextureFiltering::Nearest);
	texture->setMinificationFilteringMode(TextureFiltering::Nearest);
	return std::unique_ptr<Texture>(texture);
}

//-----------------------------------------------------------------------------

Texture::Texture(const char* _data, u32 _width, u32 _height, Format _format, FragmentType _fragmentType)
	: TextureBase(GL_TEXTURE_2D, _width, _height)
{
	bind(0);

	const s32 format = formatToGlValue(_format);
	const s32 fragmentType = fragmentTypeToGlValue(_fragmentType);

	glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, fragmentType, _data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
