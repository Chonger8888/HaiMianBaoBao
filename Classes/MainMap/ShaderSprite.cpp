#include "ShaderSprite.h"

static  const GLchar *transparentshader =
	"                                                       \n\
	#ifdef GL_ES                                            \n\
	precision lowp float;                                   \n\
	#endif                                                  \n\
	varying vec4 v_fragmentColor;                           \n\
	varying vec2 v_texCoord;                                \n\
	uniform sampler2D u_texture;                            \n\
	void main()                                             \n\
	{                                                       \n\
	vec4 texColor = texture2D(u_texture, v_texCoord);   \n\
	float grey = dot(texColor.rgb, vec3(0,0,255)); \n\
	if(texColor.a > 0.0) \n\
	gl_FragColor = vec4(0,255,0, texColor.a); \n\
	else \n\
	gl_FragColor = texColor; \n\
	}";

ShaderSprite* ShaderSprite::create(const char *pszFileName)
{
	ShaderSprite *pRet = new ShaderSprite();
	if(pRet && pRet->initWithFile(pszFileName))
		{
			pRet->autorelease();
			return pRet;
		}
	else
		{
		        delete pRet;
		        pRet = NULL;
		        return NULL;
		}
}

bool ShaderSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
	do
		{
			CC_BREAK_IF(!CCSprite::initWithTexture(pTexture, rect));
        
		        // 加载顶点着色器和片元着色器
		        m_pShaderProgram = new  CCGLProgram();
		        m_pShaderProgram ->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, transparentshader);
        
		        CHECK_GL_ERROR_DEBUG();
		        
		        // 启用顶点着色器的attribute变量，坐标、纹理坐标、颜色
		        m_pShaderProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		        m_pShaderProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		        m_pShaderProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		        
		        CHECK_GL_ERROR_DEBUG();
		        
		        // 自定义着色器链接
		        m_pShaderProgram->link();
		        
		        CHECK_GL_ERROR_DEBUG();
		        
		        // 设置移动、缩放、旋转矩阵
		        m_pShaderProgram->updateUniforms();
		        
		        CHECK_GL_ERROR_DEBUG();
		        
		        return true;
		}while(0);
	return false;
}

void ShaderSprite::draw(void)
{
	CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
    
	CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");

	CC_NODE_DRAW_SETUP();

	//
	// 启用attributes变量输入，顶点坐标，纹理坐标，颜色
	//
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
	ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);

	m_pShaderProgram->use();
	m_pShaderProgram->setUniformsForBuiltins();

	// 绑定纹理到纹理槽0
	ccGLBindTexture2D(m_pobTexture->getName());

	#define kQuadSize sizeof(m_sQuad.bl)
	
	long offset = (long)&m_sQuad;

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	CHECK_GL_ERROR_DEBUG();

	CC_INCREMENT_GL_DRAWS(1);
	CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}