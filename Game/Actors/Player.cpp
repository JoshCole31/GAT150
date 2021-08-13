#include "Player.h"
#include "Math/MathUtils.h"
//#include "Projectile.h"
#include "Engine.h"
//#include "Enemy.h"
#include <memory>

Player::Player(const jc::Transform& transform, std::shared_ptr<jc::Texture> texture, float speed) : jc::Actor{ transform, texture }, speed{ speed }
{
}

void Player::Initialize()
{

	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localposition = jc::Vector2{ -14,0 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localposition = jc::Vector2{ 0,5 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localposition = jc::Vector2{ 0,-5 };
	AddChild(std::move(locator));

	//std::unique_ptr shooter = std::make_unique<Actor>(jc::Transform{}, scene-> engine->Get<jc::ResourceSystem>()->Get<jc::Shape>("shooterbottom.txt"));
	//std::unique_ptr shooter->transform.localposition = jc::Vector2{ 3,-5 };
	//AddChild(std::move(shooter));

	//std::unique_ptr shootertop = std::make_unique<Actor>(jc::Transform{}, scene->engine->Get<jc::ResourceSystem>()->Get<jc::Shape>("shootertop.txt"));
	//shootertop->transform.localposition = jc::Vector2{ 3,5 };
	//AddChild(std::move(shootertop));

	//std::unique_ptr locatorb = std::make_unique<Actor>();
	//locatorb->transform.localposition = jc::Vector2{ -5,0 };
	//locatorb->transform.localrotation = jc::DegToRad(180);
	//AddChild(std::move(locatorb));

	scene->engine->Get<jc::EventSystem>()->Subcribe("PlayerDead", std::bind(&Player::OnPlayerDead, this, std::placeholders::_1));

}
void Player::Update(float dt)
{
	Actor::Update(dt);


	float thrust = 0;
	
	if (scene->engine->Get<jc::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == jc::InputSystem::eKeyState::Held)transform.rotation -= 5 * dt;//input.x = -1;
	if (scene->engine->Get<jc::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == jc::InputSystem::eKeyState::Held)transform.rotation += 5 * dt;//input.x = -1;
	if (scene->engine->Get<jc::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == jc::InputSystem::eKeyState::Held)thrust = speed;//input.x = -1;


	//acceleration
	jc::Vector2 acceleration;
	acceleration += jc::Vector2::Rotate(jc::Vector2::right, transform.rotation) * thrust;

	//jc::Vector2 gravity = (jc::Vector2{ 400,300 } - transform.position).Normalized()* 50;
	//jc::Vector2 gravity = jc::Vector2::down* 50;
	//acceleration += gravity;

	velocity += acceleration * dt;
	transform.position += velocity * dt;

	velocity *= 0.985f;

	transform.position.x = jc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = jc::Wrap(transform.position.y, 0.0f, 600.0f);

	//fire
	/*fireTimer -= dt;
	if (fireTimer <=0 && Core::Input::IsPressed(VK_SPACE)) 
	{
		fireTimer = fireRate;
		{
		jc::Transform t = children[1]->transform;
				t.scale = 2;

				std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<jc::ResourceSystem>()->Get<jc::Shape>("projectile.txt"), 600.0f);
				projectile->tag = "Player";

				scene->Addactor(std::move(projectile));
		}
		{
			jc::Transform t = children[2]->transform;
			t.scale = 2;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<jc::ResourceSystem>()->Get<jc::Shape>("projectile.txt"), 600.0f);
			projectile->tag = "Player";

			scene->Addactor(std::move(projectile));
		}
		
		scene->engine->Get<jc::AudioSystem>()->PlayAudio("PlayerShoot");

	}
	scene->engine->Get<jc::ParticleSystem>()->Create(children[5]->transform.position, 3, 2, colors, 50,children[5]->transform.rotation,jc::DegToRad(30));*/
	scene->engine->Get<jc::ParticleSystem>()->Create(children[0]->transform.position, 3, 1, scene->engine->Get<jc::ResourceSystem>()->Get<jc::Texture>("Particle1.png", scene->engine->Get<jc::Renderer>()), 50, 50, jc::DegToRad(30));
	//jc::Vector2{ transform.position.x - 45,transform.position.y }
}
void Player::OnCollision(Actor * actor)
{
	//return;
		//if (dynamic_cast<Enemy*>(actor))
		//{
		//	// destroy = true;
		//	scene->engine->Get<jc::ParticleSystem>()->Create(transform.position, 200, 1, jc::Color::White, 50);
		//	scene->engine->Get<jc::AudioSystem>()->PlayAudio("explosion");
		//	jc::Event event;
		//	/*event.name = "PlayerDead";
		//	event.data = std::string("yes i'm dead!");
		//	scene->engine->Get<jc::EventSystem>()->Notify(event);*/
		//	event.name = "PlayerHit";
		//	event.data = 1;
		//	scene->engine->Get<jc::EventSystem>()->Notify(event);
		//}
}

void Player::OnPlayerDead(const jc::Event& event)
{
	destroy = true;
}