#include "julie/Texture.hpp"
#include "julie/TextureTiling.hpp"
#include "julie/TextureFiltering.hpp"

#include "formats/stb_image.hpp"

#include "utils/Utils.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> Texture::loadFromFile(std::string_view _filePath)
{
	int width, height, channels;
	u8* buffer = stbi_load(_filePath.data(), &width, &height, &channels, STBI_default);

	ASSERTM(buffer, "Can not load texture from file: {}", _filePath);
	ASSERTM(width > 0 && height > 0, "Invalid texture size");
	ASSERTM(channels == 3 || channels == 4, "Unsupported channels count");
	if (!buffer || width <= 0 || height <= 0 || !(channels == 3 || channels == 4))
	{
		stbi_image_free(buffer);
		return nullptr;
	}

	const Format format = channels == 4 ? Format::Rgba : Format::Rgb;

	Texture* texture = new Texture(buffer, width, height, format, FragmentType::UnsignedByte);
	texture->setMagnificationFilteringMode(TextureFiltering::Linear);
	texture->setMinificationFilteringMode(TextureFiltering::LinearMipmapLinear);

	stbi_image_free(buffer);

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

Texture::Texture(const u8* _data, u32 _width, u32 _height, Format _format, FragmentType _fragmentType)
	: TextureBase(GL_TEXTURE_2D, _width, _height)
{
	bind(0);

	const s32 format = formatToGlValue(_format);
	const s32 fragmentType = fragmentTypeToGlValue(_fragmentType);

	glTexImage2D(getType(), 0, format, _width, _height, 0, format, fragmentType, _data);
	glGenerateMipmap(getType());
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
