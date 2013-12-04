#pragma once
#include "Type.h"

namespace EasyD3D
{
    enum class StopwatchStatus { Paused, Running };

    // 스톱워치 클래스. 시간 측정에 쓰인다.
    class Stopwatch
    {
        const static llong CountPerSecond;
        llong countStarted;
        llong countPaused;
        llong countLastTick;

    public:
        // 새 스톱워치 객체를 생성한다
        // Status : 새로 생성된 스톱워치가 일시정지된 상태일지, 실행중인 상태일지 결정한다 (기본값 : Paused)
        Stopwatch(StopwatchStatus Status = StopwatchStatus::Paused);

        // 멈춰있는 스톱워치를 작동시킨다. 이미 작동중이었을경우, 아무런일도 일어나지 않는다.
        void Start();
        // 작동중인 스톱워치를 정지시킨다. 이미 멈춰있었을경우, 아무런일도 일어나지 않는다.
        void Pause();

        // 스톱워치가 시작되고나서 총 경과한 시간을 반환한다.
        // 반환값 : 스톱워치가 시작되고나서 경과된 총 시간. (단위 : 초)
        double getTime() const;
        // 스톱워치가 현재 시간을 재는중인지, 일시정지된 상태인지 여부를 반환한다.
        // 반환값 : 현재 스톱워치의 상태
        StopwatchStatus getStatus() const { return countPaused ? StopwatchStatus::Paused : StopwatchStatus::Running; }

        // 마지막으로 Tick() 함수를 호출한지 시간이 얼마나 지났는지 반환한다.
        // 반환값 : 마지막으로 Tick() 함수를 호출하고나서 경과된 총 시간. (단위 : 초)
        double Tick();
    };
}