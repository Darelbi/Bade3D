/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeRenderer.hpp"
#include "QueueExecutor.hpp"

namespace Bade{
	
	/** This class decouple client from QueueExecutor interface.
		Removing this class requires to create a new interface from
		wich QueueExecutor should inherit.*/
	class ConcreteRenderer: public Renderer{
		
		QueueExecutorPtr	queueExecutor;
		
	public:
		
		ConcreteRenderer( QueueExecutorPtr executor);
	
		void render() override;
	};
} // namespace Bade