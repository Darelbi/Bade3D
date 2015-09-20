/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "ConcreteRenderer.hpp"

namespace Bade{

	ConcreteRenderer::ConcreteRenderer( QueueExecutorPtr executor){
		queueExecutor = executor;
	}

	void ConcreteRenderer::render(){
		while( queueExecutor->render()) ;
	}
} // namespace Bade