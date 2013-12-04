#pragma once
#include "Type.h"

namespace EasyD3D
{
    enum class StopwatchStatus { Paused, Running };

    // �����ġ Ŭ����. �ð� ������ ���δ�.
    class Stopwatch
    {
        const static llong CountPerSecond;
        llong countStarted;
        llong countPaused;
        llong countLastTick;

    public:
        // �� �����ġ ��ü�� �����Ѵ�
        // Status : ���� ������ �����ġ�� �Ͻ������� ��������, �������� �������� �����Ѵ� (�⺻�� : Paused)
        Stopwatch(StopwatchStatus Status = StopwatchStatus::Paused);

        // �����ִ� �����ġ�� �۵���Ų��. �̹� �۵����̾������, �ƹ����ϵ� �Ͼ�� �ʴ´�.
        void Start();
        // �۵����� �����ġ�� ������Ų��. �̹� �����־������, �ƹ����ϵ� �Ͼ�� �ʴ´�.
        void Pause();

        // �����ġ�� ���۵ǰ��� �� ����� �ð��� ��ȯ�Ѵ�.
        // ��ȯ�� : �����ġ�� ���۵ǰ��� ����� �� �ð�. (���� : ��)
        double getTime() const;
        // �����ġ�� ���� �ð��� ���������, �Ͻ������� �������� ���θ� ��ȯ�Ѵ�.
        // ��ȯ�� : ���� �����ġ�� ����
        StopwatchStatus getStatus() const { return countPaused ? StopwatchStatus::Paused : StopwatchStatus::Running; }

        // ���������� Tick() �Լ��� ȣ������ �ð��� �󸶳� �������� ��ȯ�Ѵ�.
        // ��ȯ�� : ���������� Tick() �Լ��� ȣ���ϰ��� ����� �� �ð�. (���� : ��)
        double Tick();
    };
}