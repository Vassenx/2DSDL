TriggerComponent::TriggerComponent(std::string t, int xPos, int yPos, int size) : tag(t) {
	collider.x = xPos;
	collider.y = yPos;
	collider.h = collider.w = size;
}

void onTrigger(TransformComponent& tComp){
	if (tag == "water") {
		tComp.gravity = -0.3f;
	}
}