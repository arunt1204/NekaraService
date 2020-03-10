#pragma once

#include <iostream>
#include "ProjectState.h"
#include <mutex> 
#include <assert.h>
#include <chrono>

namespace NS {

	std::mutex _obj;

	class NekaraService {
	private:
		ProjectState _projectState;
		int _currentThread;
		int _seed;
		bool _debug = false;
		int _thread_ID_generator;
		int _resource_ID_generator;

	public:
		NekaraService()
		{
			// getting seed from Nanoseconds
			std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
			auto duration = now.time_since_epoch();
			auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

			_currentThread = 0;
			_thread_ID_generator = 1000;
			_resource_ID_generator = 100000;
			_seed = nanoseconds.count() % 999;
			std::cout << "Your Program is being tested with random seed: " << _seed << "\n";
			std::cout << "Give the same Seed to the Testing Service for a Re-Play." << "\n";
			srand(_seed);

			_obj.lock();
			sem_t _obj1;
			sem_init(&_obj1, 0, 0);
			_projectState._th_to_sem[0] = _obj1;
			_obj.unlock();
		}

		NekaraService(int _seed)
		{
			_currentThread = 0;
			_thread_ID_generator = 1000;
			_resource_ID_generator = 100000;
			this->_seed = _seed;
			std::cout << "Your Program is being tested with seed: " << this->_seed << "\n";
			srand(_seed);

			_obj.lock();
			sem_t _obj1;
			sem_init(&_obj1, 0, 0);
			_projectState._th_to_sem[0] = _obj1;
			_obj.unlock();
		}

		void CreateThread()
		{
			if (_debug) {
				std::cout << "CT-entry" << "\n";
			}

			_obj.lock();
			_projectState.ThreadCreation();
			_obj.unlock();

			if (_debug) {
				std::cout << "CT-exit" << "\n";
			}

		}

		void StartThread(int _threadID)
		{
			if (_debug) {
				std::cout << "ST-entry: " << _threadID << "\n";
			}

			_obj.lock();
			_projectState.ThreadStarting(_threadID);
			sem_t _obj1 = _projectState._th_to_sem.find(_threadID)->second;
			_obj.unlock();

			sem_wait(&_obj1);

			if (_debug) {
				std::cout << "ST-exit: " << _threadID << "\n";
			}

		}

		void EndThread(int _threadID)
		{
			if (_debug) {
				std::cout << "ET-entry: " << _threadID << "\n";
			}

			_obj.lock();
			_projectState.ThreadEnded(_threadID);
			_obj.unlock();

			ContextSwitch();

			if (_debug) {
				std::cout << "ET-exit: " << _threadID << "\n";
			}

		}

		void CreateResource(int _resourceID)
		{
			_obj.lock();
			_projectState.AddResource(_resourceID);
			_obj.unlock();
		}

		void DeleteResource(int _resourceID)
		{
			_obj.lock();
			_projectState.RemoveResource(_resourceID);
			_obj.unlock();
		}

		void BlockedOnResource(int _resourceID)
		{
			_obj.lock();
			_projectState.BlockThreadOnResource(_currentThread, _resourceID);
			_obj.unlock();

			ContextSwitch();
		}

		void BlockedOnAnyResource(int _resourceID[], int _size)
		{
			_obj.lock();
			_projectState.BlockThreadonAnyResource(_currentThread, _resourceID, _size);
			_obj.unlock();

			ContextSwitch();
		}

		void SignalUpdatedResource(int _resourceID)
		{
			_obj.lock();
			_projectState.UnblockThreads(_resourceID);
			_obj.unlock();
		}

		int GenerateThreadTD()
		{
			int _threadID;
			_obj.lock();
			_threadID = _thread_ID_generator;
			_thread_ID_generator++;
			_obj.unlock();

			return _threadID;
		}

		int GenerateResourceID()
		{
			int _resourceID;
			_obj.lock();
			_resourceID = _resource_ID_generator;
			_resource_ID_generator++;
			_obj.unlock();

			return _resourceID;
		}

		bool CreateNondetBool()
		{
			bool _NondetBool;
			_obj.lock();
			_NondetBool = rand() % 2;
			_obj.unlock();

			return _NondetBool;
		}

		int CreateNondetInteger(int _maxValue)
		{
			int _NondetInteger;
			_obj.lock();
			_NondetInteger = rand() % _maxValue;
			_obj.unlock();

			return _NondetInteger;
		}

		void ContextSwitch()
		{
			if (_debug) {
				std::cout << "CS-entry" << "\n";
			}

			WaitForPendingTaskCreations();

			int _next_threadID = -99;
			int _current_thread;
			bool _current_thread_running = false;
			sem_t _next_obj1;
			sem_t _crr_obj1;

			_obj.lock();
			_current_thread = this->_currentThread;

			std::map<int, sem_t>::iterator _ct_it = _projectState._th_to_sem.find(_current_thread);
			if (_ct_it != _projectState._th_to_sem.end())
			{
				_current_thread_running = true;
				_crr_obj1 = _ct_it->second;
			}

			int _size_t_s = _projectState._th_to_sem.size();
			int _size_b_t = _projectState._blocked_task.size();
			int _size = _size_t_s - _size_b_t;

			if (_size == 0 && _size_t_s != 0)
			{
				std::cerr << "ERROR: Deadlock detected" << ".\n";
				abort();
			}

			if (_size == 0 && _size_t_s == 0)
			{
				_obj.unlock();
				return;
			}

			int _randnum = rand() % _size;

			int _i = 0;

			for (std::map<int, sem_t>::iterator _it = _projectState._th_to_sem.begin(); _it != _projectState._th_to_sem.end(); ++_it)
			{
				std::map<int, std::set<int>*>::iterator _bt_it = _projectState._blocked_task.find(_it->first);

				if (_bt_it == _projectState._blocked_task.end())
				{
					if (_i == _randnum)
					{
						std::cout << "Ctrl given to TaskID:" << _it->first << "\n";

						_next_threadID = _it->first;
						_next_obj1 = _it->second;
						break;
					}
					_i++;
				}
			}
			_obj.unlock();

			if (_next_threadID == _current_thread)
			{
				// no op
			}
			else
			{
				_obj.lock();
				_currentThread = _next_threadID;
				_obj.unlock();

				sem_post(&_next_obj1);

				if (_current_thread_running)
				{
					sem_wait(&_crr_obj1);
				}
			}

			if (_debug) {
				std::cout << "CS-exit" << "\n";
			}
		}

		void WaitForPendingTaskCreations()
		{
			while (true)
			{
				_obj.lock();
				if (_projectState.numPendingTaskCreations == 0)
				{
					_obj.unlock();
					return;
				}
				_obj.unlock();
			}
		}

		void WaitforMainTask()
		{
			if (_debug) {
				std::cout << "WMT-entry" << "\n";
			}

			EndThread(0);

			if (_debug) {
				std::cout << "WMT-exit" << "\n";
			}
		}
	};

}
