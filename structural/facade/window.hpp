#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "viewport.hpp"

struct IBuffer;

class Window
{
	std::string m_title;
	Size m_size;

	std::vector<std::shared_ptr<IBuffer>> buffers;
	std::vector<std::shared_ptr<Viewport>> viewports;

public:
	explicit Window(std::string window_title, Size sz)
		:	m_title{std::move(window_title)},
			m_size{std::move(sz)}
	{}

	void show() const
	{
		std::cout << "-=-=-=-=-=-=-=-=- " << m_title << " " << m_size << " -=-=-=-=-=-=-=-=-" << std::endl;
		for(const auto& vp : viewports)
		{
			vp->update();
		}
		std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
	}

	void add_buffer(std::shared_ptr<IBuffer> buffer)
	{
		buffers.emplace_back(std::move(buffer));
	}

	void add_viewport(std::shared_ptr<Viewport> viewport)
	{
		viewports.emplace_back(std::move(viewport));
	}

	const std::string& title() const
	{
		return m_title;
	}

	const Size& size() const
	{
		return m_size;
	}
};

