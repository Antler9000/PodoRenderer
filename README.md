# PodoRenderer
D3D12, Win32, C++을 이용하여 구현 중인 렌더링 엔진입니다.

대규모 월드의 렌더링 부하를 견디는 것을 목표로 하고 있습니다.

현재 기초적인 렌더링 기능 구현 과정에 있습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 목차
- [1. 데모 스크린샷](#1-데모-스크린샷)
- [2. 실행 방법](#2-실행-방법)
- [3. 주요 기능](#3-주요-기능)
- [4. 측정 성능](#4-측정-성능)
- [5. 구현 구조](#5-구현-구조)
- [6. 구현 예정](#6-구현-예정)
- [7. 구현 제외](#7-구현-제외)
- [8. 외부 항목](#8-외부-항목)
- [9. 참고 자료](#9-참고-자료)

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 1. 데모 스크린샷
아직 구현하지 않음

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 2. 실행 방법
### 2.1. 실행 환경
아직 구현하지 않음

<br>




### 2.2. 빌드 방법
아직 구현하지 않음

<br> 




### 2.4. 실행 방법
아직 구현하지 않음

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 3. 주요 기능
아직 구현하지 않음

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 4. 측정 성능
### 6.1. 측정 환경
아직 구현하지 않음

<br>




### 6.2. 측정 방식
아직 구현하지 않음

<br>




### 6.3. 측정 결과
아직 구현하지 않음

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 5. 구현 구조
### 5.1. 폴더 구조
Frank Luna D3D12 입문 도서의 폴더 구조를 참고하여 다음과 같은 하위 폴더들을 두었습니다 [1].

<br>

- `Code`  
  : 헤더 파일 폴더(=`추가 포함 디렉토리`)와 소스 파일 폴더가 위치합니다.

- `External`  
  : 리포지토리 내부에 직접 포함된 외부 항목이 위치합니다.

- `IntDir` ( =`중간 디렉토리`)  
  : 컴파일 결과물이 위치합니다.

- `Model`  
  : 오브젝트, 애니메이션 파일들이 위치합니다.

- `OutDir` (=`출력 디렉토리`, `작업 디렉토리`)  
  : 링크 결과물과, 런타임들이 위치합니다.

- `Shader`  
  : HLSL 셰이더 파일들이 위치합니다.

- `Texture`  
  : DDS 텍스처 파일들이 위치합니다.

<br>




### 5.2. 빌드 대상
본 리포지토리는 Visual Studio의 `.vcxproj`를 통해 빌드 설정을 관리하고 있습니다.

일반적으로 Visual Studio에서 응용 프로그램의 빌드와 실행은 다음과 같이 이뤄집니다.
| 단계 | 직접 입력 | 직접 입력 대상 | 간접 입력 | 간접 입력 대상 명시 | 간접 입력 대상 경로 명시 | 출력 | 출력 경로 |
|---|---|---|---|---|---|---|---|
| 전처리 + 컴파일 | `.cpp` | 프로젝트에 포함된 각 `.cpp` 파일 | `.h`, `.inl` | `#include <xxx.h>`, `#include "xxx.h"`| (`프로젝트 속성` > `C/C++` > `일반` > `추가 포함 디렉토리` > `편집`) | `.obj` | `중간 디렉토리` |
| 링크 | `.obj` | 컴파일된 `.obj` 파일들 | `.lib` | `#pragma comment(lib, "xxx.lib")` <br> or <br> (`프로젝트 속성` > `링커` > `입력` > `추가 종속성` > `편집`) | (`프로젝트 속성` > `링커` > `일반` > `추가 라이브러리 디렉토리` > `편집`) | `.exe` |  `출력 디렉토리` |
| 실행 | `.exe` | 링크된 `.exe` |  `.dll` | 링크 시점에 임포트 라이브러리를 링크 <br> (로드-타임 동적 링킹) <br> or <br> 실행 중 `LoadLibraryA(..)` 함수 사용 <br> (런-타임 동적 링킹) [2] | 해당 없음(`.dll`을 `.exe`의 디렉토리에 복사해주는 것이 일반적) | 프로세스 | 해당 없음 |

<br>

D3D12 애플리케이션의 빌드와 실행에 필요한 대상들을 가장 간단히 나열하면 다음과 같습니다 [3].
| 대상 | 관리 주체 | 내용물 | 목적 | 경로 | 세팅 방법 |
|---|---|---|---|---|---|
| Windows SDK | Visual Studio Installer | `.h`, `.inl`, `.lib` | 윈도우 앱 빌드에 필요한 헤더, 라이브러리 사용 |`C:\Program Files (x86)\Windows Kits` | 경로는 기본 설정되어 있음, <br> 무엇을 사용할지만 다음처럼 명시하면 됨 <br> `#include <d3d12.h>` <br> `#include <dxgi1_6.h>` <br> `#pragma comment(lib, "dxgi.lib")` <br> `#pragma comment(lib, "D3D12.lib")` <br> ... |
| DirectX Header | Microsoft Github Repository | `.h` | `d3dx12*.h` 헬퍼 구조체, 헬퍼 함수 사용 | https://github.com/microsoft/DirectX-Headers | 수동으로 다운로드 받아 프로젝트에 포함 |
| D3D12 Runtime | Windows | `.dll` | 응용 프로그램 구동에 필요한 런타임 사용 | `C:\Windows\System32` | 경로는 기본 설정되어 있음, <br> 임포트 라이브러리인 `D3D12.lib`을 통해 로드-타임 동적 링킹이 일어나므로 별도의 런-타임 동적 링킹 또한 필요 없음 |

<br>

본 리포지토리는 Frank Luna의 D3D12 입문 도서가 NuGet으로 최신 런타임을 복원하는 방식을 참고하였습니다 [1]. 다만 해당 도서가 NuGet으로 관리하지 않고 직접 파일을 포함하던 대상들까지 모두 NuGet으로 복원되도록 확장 적용하였습니다.
| 대상 | 목적 | 파일 |
|---|---|---|
| DirectX 12 Agility SDK | 최신 D3D12 기능 사용 | `.h`, `.dll` |
| DirectXTK12 | DirectX12 툴 헤더, 라이브러리 사용 | `.h`, `.inl`, `.lib` |
| DirectX Shader Compiler (DXC) | HLSL 셰이더 파일 컴파일 | `.h`, `.lib`, `.dll` |

<br>




### 5.3. 입력 처리
일반적인 윈도우 메시지 처리 방식을 사용하고 있습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 6. 구현 예정
- **단일 PSO 렌더링**
  - 외부 에셋 파일 로드
  - 정점 버퍼, 인덱스 버퍼, 텍스처
  - 디폴트 힙 자원 업로드(`DirectX::ResourceUploadBatch`), CPU-GPU 동기화(`Fence`), 로딩 버튼 동기화
  - VBV, IBV, SRV 서술자
  - 오브젝트 테이블
  - 상수 버퍼
  - 업로드 힙 자원 관리(`DirectX::GraphicsMemory`), CPU-GPU 동기화(`Fence`)
  - CBV 서술자
  - 원근 투영, 조명, 텍스처 매핑, 노말 매핑, 거리별 안개 셰이더
  - 입력 서명
  - 루트 서명
  - 파이프라인 상태 객체
  - SDR 감마 인코딩-디코딩
  - 카메라 조작 기능
  - 오브젝트 수 조절 기능
  - 가상 CPU 부하 조절 기능

<br>

- **단일 PSO 렌더링 최적화**
  - 에셋 경량화             : 사전 생성 LOD
  - 로딩 대상 선별          : 로딩 정책
  - 로딩 로직 최적화        : 로딩 전용 파일 포맷
  - 로딩과 렌더간 병렬화    : 파일 읽기용 CPU 스레드
  - 업로드 대상 선별        : 업로드 힙 자원 관리 정책, 디폴트 힙 자원 관리 정책
  - 업로드 로직 최적화      : `DirectX::ResourceUploadBatch`, `DirectX::GraphicsMemory` 비용 검증
  - 업로드와 렌더간 병렬화  : Copy Queue
  - 루트 서명 직접화        : 루트 서술자, 루트 상수 
  - 루트 서명 간접화        : 서술자 테이블, 셰이더 자원 테이블 간접 인덱싱, 바인드리스 서술자힙 접근
  - 루트 서명 정렬          : 변경 횟수가 많은 것부터 내림차순으로 정렬
  - 대상 선별               : 오브젝트 절두체 선별, 광원 절두체 선별
  - 그리기 명령 횟수 축소   : 인스턴싱
  - 그리기 명령 병렬화      : 그리기 명령 분할 스레드
  - 그리기 명령 재사용      : 번들
  - 셰이더 최적화           : 분기 수 조절, 로컬리티 개선 등

<br>

- **다중 PSO 렌더링**
  - 조형 PSO : 변위 매핑(지형, 수면), 스킨 애니메이션, 파티클
  - 조명 PSO : 블랜딩, 정적 환경 매핑, 동적 환경 매핑, 그림자 매핑, SSAO, 레이 트레이싱

<br>

- **다중 PSO 렌더링 최적화**
  - 방식 비교 : 포워드 렌더링 vs 포워드+ 렌더링 vs 지연 렌더링(+다중 렌더 타겟), 사전 생성 LOD vs 기하 셰이더 런타임 LOD vs 테셀레이션 런타임 LOD vs 메쉬 셰이더 런타임 LOD, 단일 렌더 타겟 동적 입방체 그리기 vs 다중 렌더 타겟 어레이 동적 입방체 그리기
  - PSO 내 최적화 : 루트 서명 직접화, 루트 서명 간접화, 루트 서명 정렬, 셰이더 최적화
  - PSO 간 최적화 : Placed Resource 공간 활용, 입력 슬롯 분할, PSO 변경 횟수 절약, 루트 서명 표준화

<br>

- **제시 개선**
  - 지연 한도 설정(`SetMaximumFrameLatency`, `WaitableObject`)
  - HDR 제시(톤 매핑, 색역 매핑, PQ 전달 함수)
  - 백버퍼, GUI 해상도와 독립적인 렌더 해상도 조절 기능

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 7. 구현 제외
- **디바이스 소실 대응**  
  렌더링 최적화라는 본 프로젝트의 핵심 목적에서 벗어나기에 제외하였습니다.

<br>

- **윈도우 DPI 설정값 자동 반영**  
  본 렌더링 엔진은 DPI 설정값에 의한 윈도우의 자동 스케일링으로 화면이 훼손되지 않도록 DPI AWARENESS를 매니페스트에 명시하였습니다. 윈도우의 DPI 설정값을 반영하는 로직을 작성하지 않고, 대신 옵션에서 GUI의 물리적 픽셀 배율을 50%, 75%, 100%, 125%, 150% 중에서 명시적으로 선택할 수 있도록 하였습니다.

<br>

- **안티 앨리어싱**
  대중화된 QHD, UHD에 적합한 안티 앨리어싱 기법은 추가 학습이 필요하기에 프로젝트 규모를 제한하고자 제외하였습니다. 

<br>

- **심화 렌더링 기법**
  캐스케이드 셰도우 매핑, 복셀 광역 조명과 같은 심화 렌더링 기법은 추가 학습이 필요하기에 프로젝트 규모를 제한하고자 제외하였습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 8. 외부 항목
개발 및 빌드를 위해 다음 SDK, 툴킷, 라이브러리, 도구를 사용합니다.

<br>




### 8.1. DirectX 12 Agility SDK
- 목적
  - 윈도우 업데이트와 상관 없이 최신 D3D12 헤더, 런타임 사용

- 사용 방식
  - NuGet 패키지 관리 (Microsoft.Direct3D.D3D12)
  
- 복원 위치
  - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.<버전명>`

- 라이선스 종류
  - MICROSOFT SOFTWARE LICENSE
  - MIT License

- 라이선스 위치
  - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.<버전명>\LICENSE.txt`
  - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.<버전명>\LICENSE-CODE.txt`

<br>




### 8.2. DirectX Tool Kit (DirectXTK12)
- 목적
  - Direct3D 12 유틸리티 라이브러리 사용

- 사용 방식
  - NuGet 패키지 관리 (directxtk12_desktop_win10)

- 복원 위치
  - `PodoRenderer\packages\directxtk12_desktop_win.<버전명>`

- 라이선스 종류
  - MIT License

- 라이선스 위치
  - `PodoRenderer\packages\directxtk12_desktop_win10.<버전명>\docs\README.md` 내부 간접 링크
  - `https://github.com/microsoft/DirectXTK12/blob/main/LICENSE`

<br>




### 8.3. DirectX Shader Compiler (DXC)
- 목적
  - HLSL 셰이더 컴파일

- 사용 방식
  - NuGet 패키지 관리 (Microsoft.Direct3D.DXC)
  
- 복원 위치
  - `PodoRenderer\packages\Microsoft.Direct3D.DXC.<버전명>`

- 라이선스 종류
  - MIT License
  - LLVM Release License
  - MICROSOFT SOFTWARE LICENSE

- 라이선스 위치
  - `PodoRenderer\packages\Microsoft.Direct3D.DXC.<버전명>\LICENCE-MIT.txt`
  - `PodoRenderer\packages\Microsoft.Direct3D.DXC.<버전명>\LICENSE-LLVM.txt`
  - `PodoRenderer\packages\Microsoft.Direct3D.DXC.<버전명>\LICENSE-MS.txt`

<br>




### 8.4. PIX Event Runtime
- 목적
  - PIX 캡처

- 사용 방식
  - NuGet 패키지 관리 (WinPixEventRuntime)
  
- 복원 위치
  - `PodoRenderer\packages\WinPixEventRuntime.<버전명>`

- 라이선스 종류
  - MIT License

- 라이선스 위치
  - `PodoRenderer\packages\WinPixEventRuntime.<버전명>\license.txt`

<br>




### 8.5 Dear ImGui
- 목적
  - 옵션 GUI 제공

- 사용 방식
  - 내부 직접 포함(`PodoRenderer\External\imgui`)
  - 예제 수정 사용(`PodoRenderer\Code\Header\Alloc.h`)

- 원본 리포지토리
  - ocornut/imgui  
    `https://github.com/ocornut/imgui`

- 라이선스 종류
  - MIT License

- 라이선스 위치
  - `PodoRenderer\External\imgui\LICENSE.txt`

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 9. 참고 자료
### 9.1. 인용 참고
[1] "Introduction To 3D Game Programming With DirectX 12 Second Edition" (Frank D. Luna 지음 / Mercury Learning And Information 출판 / 2025년 발행)  

[2] "Link an executable to a DLL" (Microsoft Learn / 2026년 7월 방문)  
https://learn.microsoft.com/en-us/cpp/build/linking-an-executable-to-a-dll?view=msvc-170

[3] "Direct3D 12 programming environment setup" (Microsoft Learn / 2026년 7월 방문)  
https://learn.microsoft.com/en-us/windows/win32/direct3d12/directx-12-programming-environment-set-up

[4] "Getting Started with the Agility SDK" (Microsoft Dev Blogs / 2026년 7월 방문)  
https://devblogs.microsoft.com/directx/gettingstarted-dx12agility/

<br>




### 9.2. 구현 참고
"Get Started with Win32 and C++" (Microsoft Learn / 2026년 6월 방문)  
https://learn.microsoft.com/en-us/windows/win32/learnwin32/learn-to-program-for-windows

"Setting the default DPI awareness for a process" (Microsoft Learn / 2026년 7월 방문)  
https://learn.microsoft.com/en-us/windows/win32/hidpi/setting-the-default-dpi-awareness-for-a-process

"ComPtr" (microsoft / 2026년 7월 방문)  
https://github.com/Microsoft/DirectXTK/wiki/ComPtr

"The Care and Feeding of Modern Swap Chains" (Chuck Walbourn / 2026년 7월 방문)  
https://walbourn.github.io/care-and-feeding-of-modern-swapchains/  
https://walbourn.github.io/care-and-feeding-of-modern-swap-chains-2/  
https://walbourn.github.io/care-and-feeding-of-modern-swap-chains-3/

"PresentMon" (GameTechDev / 2026년 7월 방문)  
https://github.com/GameTechDev/PresentMon

<br>