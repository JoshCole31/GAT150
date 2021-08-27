#pragma once
#include "Component/Component.h"
#include "Audio/AudioChannel.h"
#include "Audio/AudioSystem.h"

namespace jc
{
	class AudioComponent : public Component
	{
	public:
		virtual void Update() override;

		void Play();
		void Stop();

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	public:
		std::string soundName;
		float volume = 1;
		float pitch = 1;
		bool loop = false;
		bool playOnAwake = false;

	private:
		AudioChannel channel;
		bool played{ false };
	};
}
