// Author: Valve Corporation
// Licence: https://github.com/ValveSoftware/source-sdk-2013/blob/master/LICENSE
#ifndef IMATERIAL_H
#define IMATERIAL_H

#include "ImageFormat.h"
#include "basetypes.h"

#include <fstream>
#include <sstream>
#include <ostream>

class IMaterialVar;

typedef uint64 VertexFormat_t;
typedef unsigned int MorphFormat_t;

enum PreviewImageRetVal_t
{
	MATERIAL_PREVIEW_IMAGE_BAD = 0,
	MATERIAL_PREVIEW_IMAGE_OK,
	MATERIAL_NO_PREVIEW_IMAGE,
};

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_MULTIPASS = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_NOALPHAMOD = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_IGNORE_ALPHA_MODULATION = (1 << 30),
};

enum MaterialPropertyTypes_t
{
	MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,
	MATERIAL_PROPERTY_OPACITY,
	MATERIAL_PROPERTY_REFLECTIVITY,
	MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS
};

class IMaterial
{
public:
	const char *	GetName() {
		typedef const char *(__thiscall* Fn)(void*);
		return Utils::GetVFunc<Fn>(this, 0)(this);
	}
	const char *			GetTextureGroupName() {
		typedef const char *(__thiscall* Fn)(void*);
		return Utils::GetVFunc<Fn>(this, 1)(this);
	}
	virtual PreviewImageRetVal_t GetPreviewImageProperties(int *width, int *height, ImageFormat *imageFormat, bool* isTranslucent) const = 0; // 2
	virtual PreviewImageRetVal_t GetPreviewImage(unsigned char *data, int width, int height, ImageFormat imageFormat) const = 0; // 3
	virtual int				GetMappingWidth() = 0; // 4
	virtual int				GetMappingHeight() = 0; // 5
	virtual int				GetNumAnimationFrames() = 0; // 6
	virtual bool			InMaterialPage(void) = 0; // 7
	virtual	void			GetMaterialOffset(float *pOffset) = 0; // 8
	virtual void			GetMaterialScale(float *pScale) = 0; // 9
	virtual IMaterial		*GetMaterialPage(void) = 0; // 10
	virtual IMaterialVar *	FindVar(const char *varName, bool *found, bool complain = true) = 0; // 11
	virtual void			IncrementReferenceCount(void) = 0; // 12
	virtual void			DecrementReferenceCount(void) = 0; // 13
	inline void AddRef() { IncrementReferenceCount(); } // 14
	inline void Release() { DecrementReferenceCount(); } // 15
	virtual int 			GetEnumerationID(void) const = 0; // 16
	virtual void			GetLowResColorSample(float s, float t, float *color) const = 0; // 17
	virtual void			RecomputeStateSnapshots() = 0; // 18
	virtual bool			IsTranslucent() = 0; // 19
	virtual bool			IsAlphaTested() = 0; // 20
	virtual bool			IsVertexLit() = 0; // 21
	virtual VertexFormat_t	GetVertexFormat() const = 0; // 22
	virtual bool			HasProxy(void) const = 0; // 23
	virtual bool			UsesEnvCubemap(void) = 0; // 24
	virtual bool			NeedsTangentSpace(void) = 0; // 25
	virtual bool			NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0; // 26
	virtual bool			NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0; // 27
	virtual bool			NeedsSoftwareSkinning(void) = 0; // 28
	void					AlphaModulate(float alpha) {
		typedef void(__thiscall* Fn)(void*, float);
		return Utils::GetVFunc<Fn>(this, 27)(this, alpha);
	}
	void					ColorModulate(float r, float g, float b) {
		typedef void(__thiscall* Fn)(void*, float, float, float);
		return Utils::GetVFunc<Fn>(this, 28)(this, r, g, b);
	}
	void					SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) {
		typedef void(__thiscall* Fn)(void*, MaterialVarFlags_t, bool);
		return Utils::GetVFunc<Fn>(this, 29)(this, flag, on);
	}
	virtual bool			GetMaterialVarFlag(MaterialVarFlags_t flag) const = 0;
	virtual void			GetReflectivity(Vector& reflect) = 0;
	virtual bool			GetPropertyFlag(MaterialPropertyTypes_t type) = 0;
	virtual bool			IsTwoSided() = 0;
	virtual void			SetShader(const char *pShaderName) = 0;
	virtual int				GetNumPasses(void) = 0;
	virtual int				GetTextureMemoryBytes(void) = 0;
	virtual void			Refresh() = 0;
	virtual bool			NeedsLightmapBlendAlpha(void) = 0;
	virtual bool			NeedsSoftwareLighting(void) = 0;
	virtual int				ShaderParamCount() const = 0;
	virtual IMaterialVar	**GetShaderParams(void) = 0;
	virtual bool			IsErrorMaterial() const = 0;
	virtual void			SetUseFixedFunctionBakedLighting(bool bEnable) = 0;
	virtual float			GetAlphaModulation() = 0;
	virtual void			GetColorModulation(float *r, float *g, float *b) = 0;
	virtual MorphFormat_t	GetMorphFormat() const = 0;
	virtual IMaterialVar *	FindVarFast(char const *pVarName, unsigned int *pToken) = 0;
	virtual void			SetShaderAndParams(KeyValues *pKeyValues) = 0;
	virtual const char *	GetShaderName() const = 0;
	virtual void			DeleteIfUnreferenced() = 0;
	virtual bool			IsSpriteCard() = 0;
	virtual void			CallBindProxy(void *proxyData) = 0;
	virtual IMaterial		*CheckProxyReplacement(void *proxyData) = 0;
	virtual void			RefreshPreservingMaterialVars() = 0;
	virtual bool			WasReloadedFromWhitelist() = 0;
	virtual bool			IsPrecached() const = 0;
};


#endif