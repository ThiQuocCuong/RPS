#include "GameController.h"

GC *GC::m_controller = nullptr;
GC *GC::gI() {
	if (!m_controller) {
		m_controller = new GC();
	}
	return m_controller;
}

GC::GC():m_lblController(nullptr),
m_sprController(nullptr),
m_resourceController(nullptr),
m_btnController(nullptr){

}

LabelController *GC::lbl() {
	if (!m_lblController) {
		m_lblController = new LabelController();
	}
	return m_lblController;
}
ButtonController *GC::btn() {
	if (!m_btnController) {
		m_btnController = new ButtonController();
	}
	return m_btnController;
}
SpriteController *GC::spr() {
	if (!m_sprController) {
		m_sprController = new SpriteController();
	}
	return m_sprController;
}
ResourceController *GC::resoure() {
	if (!m_resourceController) {
		m_resourceController = new ResourceController();
	}
	return m_resourceController;
}
FacebookController *GC::fb() {
	if (!m_fbController) {
		m_fbController = new FacebookController();
	}
	return m_fbController;
}