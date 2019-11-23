//#pragma once
//
//#include "rendering/objects/Model.hpp"
//
//class Pass
//{
//public:
//	void setTarget(FboPtr _pTarget) noexcept;
//	void setShader(ShaderPtr _pShader) noexcept;
//	void setParameters(Array< float > _parameters) noexcept;
//	void setTextures(Array< TexturePtr > _textures) noexcept;
//
//	void Run() const;
//
//	static void InitModel();
//
//private:
//	void InitBlurOffsets();
//
//private:
//	FboPtr m_pTarget;
//	ShaderPtr m_pShader;
//
//	Array< float > m_parameters;
//
//	Array< TexturePtr > m_textures;
//	Array< GLint > m_texureUniformValue;
//
//	glm::vec2 m_blurOffsets;
//
//	bool m_isDof;
//	bool m_isBlur;
//
//	static Model ms_model;
//};
