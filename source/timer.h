#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	float get_current_time() const
	{
		return pass_time;
	}

	float get_wait_time() const
	{
		return wait_time;
	}
	
	float get_remaining_time() const
	{
		return wait_time - pass_time;
	}

	void restart()
	{
		pass_time = 0;
		shotted = false;
		valid = true;
	}

	void set_wait_time(double val)
	{
		wait_time = val;
	}

	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}

	void set_on_timeout(std::function<void()> on_timeout)
	{
		this->on_timeout = on_timeout;
	}

	void pause()
	{
		paused = true;
		valid = false;
	}

	void resume()
	{
		paused = false;
		valid = true;
	}

	void on_update(double delta)
	{
		if (paused)
		{
			return;
		}

		pass_time += delta;
		if (pass_time >= wait_time)
		{
			bool can_shot = (!one_shot || (one_shot && !shotted));
			shotted = true;
			if (can_shot && on_timeout)
			{
				on_timeout();
			}
			pass_time -= wait_time; 
			if (one_shot)
			{
				valid = false;
			}
		}
	}

	bool is_valid()
	{
		return valid;
	}

	void shot()
	{
		bool can_shot = (!one_shot || (one_shot && !shotted));
		shotted = true;
		if (can_shot && on_timeout)
		{
			on_timeout();
		}
		pass_time = 0;
		if (one_shot)
		{
			valid = false;
		}
	}

private:
	double pass_time = 0;
	double wait_time = 0;
	bool paused = false;
	bool shotted = false;
	bool one_shot = false;
	bool valid = false;
	std::function<void()> on_timeout;
};

#endif // !_TIMER_H_
