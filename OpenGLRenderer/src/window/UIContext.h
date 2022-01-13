#pragma once

#include "RenderContext.h"

class UIContext : public RenderContext
{
private:
	bool m_ShowEditor;
public:
	bool Init(IWindow* window) override;

	void PreRender() override;

	void PostRender() override;

	void End() override;

	const bool ShowEditor() const { return m_ShowEditor; }
};