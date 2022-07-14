#include "C_Collider.h"
#include <math.h>
namespace C
{
	Collider::Collider(ColliderType type, GameObject* gameObject)
		:Component(gameObject), type(type)
	{
		SimpleSprite* simple = GetComponent<SimpleSprite>();
		SpriteSheet* sheet = GetComponent<SpriteSheet>();

		if (simple == nullptr && sheet == nullptr)
		{
			Debug::LogErr("No Sprite Component found above Collider Component");
			return;
		}

		if (type == ColliderType::Box)
		{
			if (simple != nullptr)
			{
				width = simple->GetFrame().width;
				height = simple->GetFrame().height;
			}
			if (sheet != nullptr)
			{
				radius = (sheet->GetFrame().width > sheet->GetFrame().height) ?
					sheet->GetFrame().width :
					sheet->GetFrame().height;
			}
		}

	}


	Collider::Collider(float width, float height, GameObject* gameObject)
		: Component(gameObject), width(width), height(height)
	{
		type = ColliderType::Box;
	}

	Collider::Collider(float radius, GameObject* gameObject)
		: Component(gameObject), radius(radius)
	{
		type = ColliderType::Circle;
	}

	Collider::~Collider()
	{
		if (isTrigger)
		{
			FindObjectOfType<TriggerCache>()->Remove(this);
		}
	}

	void Collider::Start()
	{
		if (GetComponent<PhysicsBox>() == nullptr)
		{
			isTrigger = true;
			TriggerCache* cache = FindObjectOfType<TriggerCache>();
			if (cache == nullptr) // create if doesn't exist
			{
				Debug::LogErr("No TriggerCache Object Found");
				//Engine::GetActiveScene()->GetWorld()->AddGameObject(new O::TriggerCache());
				//cache = FindObjectOfType<TriggerCache>();
			}
			cache->triggers.push_back(this);
		}
	}
	
	void Collider::Update()
	{
		
	}

	ColliderType Collider::GetType() const
	{
		return type;
	}

	xe::Rectangle C::Collider::GetBox() const
	{
		if (type != ColliderType::Box)
		{
			Debug::LogErr("Collider not of type Box");
			return Rectangle();
		}
		return Rectangle(gameObject->transform.position.x - (width * 0.5f), gameObject->transform.position.y - (height * 0.5f), width, height);
	}
	xe::Circle C::Collider::GetCircle() const
	{
		if (type != ColliderType::Circle)
		{
			Debug::LogErr("Collider not of type Circle");
			return Circle();
		}
		return Circle(gameObject->transform.position.x, gameObject->transform.position.y, radius);
	}

	Collider* C::Collider::GetTrigger()
	{
		std::vector<Collider*> triggers = FindObjectOfType<TriggerCache>()->triggers;
		for (Collider* other : triggers)
		{
			if (other != this)
			{

				if (type == ColliderType::Box && other->GetType() == ColliderType::Box)
				{
					if (BoxOnBox(other)) return other;
				}
				else if (type == ColliderType::Circle && other->GetType() == ColliderType::Circle)
				{
					if (CircleOnCircle(other)) return other;
				}
				else
				{
					if (BoxOnCircle(other)) return other;
				}
			}
		}
		return nullptr;
	}

	bool Collider::BoxOnBox(Collider* other)
	{
		Rectangle otherBox = other->GetBox();

		if (GetBox().x < otherBox.x + otherBox.width &&
			GetBox().x + GetBox().width > otherBox.x &&
			GetBox().y < otherBox.y + otherBox.height &&
			GetBox().y + GetBox().height > otherBox.y)
		{
			return true;
		}
		return false;
	}
	bool Collider::CircleOnCircle(Collider* other)
	{
		Circle otherCircle = other->GetCircle();

		if (GetCircle().radius + otherCircle.radius >
			sqrtf(powf(otherCircle.x - GetCircle().x, 2) + powf(otherCircle.y - GetCircle().y, 2)))
		{
			return true;
		}
		return false;

	}
	bool Collider::BoxOnCircle(Collider* other)
	{
		Debug::LogWarn("Box on Circle Collision not yet implemented");
		return false;
	}

}
