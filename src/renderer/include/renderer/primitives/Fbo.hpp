//#pragma once
//
//#include "renderer/Types.hpp"
//
//#include <boost/noncopyable.hpp>
//
//#include <memory>
//
////-----------------------------------------------------------------------------
//
//namespace jl {
//
////-----------------------------------------------------------------------------
//
//class Texture;
//
//class Fbo : boost::noncopyable
//{
//public:
//	static std::unique_ptr<Fbo> create();
//
//	static void setScreenBufferId(u32 _id);
//	static Fbo s_screen;
//
//public:
//	~Fbo();
//
//	void bind() const noexcept;
//
//	const Texture * getColorTexture() const noexcept { return m_colorTexture.get(); }
//	const Texture * getDepthTexture() const noexcept { return m_depthTexture.get(); }
//
//private:
//	Fbo() noexcept;
//
//private:
//	u32 m_id;
//
//	std::unique_ptr<Texture> m_colorTexture;
//	std::unique_ptr<Texture> m_depthTexture;
//};
//
////-----------------------------------------------------------------------------
//
//} // namespace jl
//
////-----------------------------------------------------------------------------
