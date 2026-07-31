# PodoRenderer
D3D12, Win32, C++을 이용하여 구현 중인 렌더링 엔진입니다.

대규모 월드의 렌더링 부하를 견디는 것을 목표로 하고 있습니다.

현재 기초적인 렌더링 기능 구현 과정에 있습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 목차
- [1. 스크린샷](#1-스크린샷)
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
## 1. 스크린샷
[시작 로딩]
![시작 로딩 스크린샷](docs/screenshot1.png)

[메인 렌더링]
![메인 렌더링 스크린샷](docs/screenshot2.png)

[메뉴 및 옵션]
![메뉴 및 옵션 스크린샷](docs/screenshot3.png)

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 2. 실행 방법
### 2.1. 최소 사양
|구분|최소 사양|
|-------------|---------------------------|
|운영체제     |Windows 10 버전 1803 이상  |
|CPU          |미정                       |
|GPU 피처 레벨|D3D_FEATURE_LEVEL_12_0 이상|
|RAM          |미정                       |
|저장 장치    |미정                       |


- HDR 제시, 레이 트레이싱, 메쉬 셰이더 등의 옵션은 추가 사양이 필요할 수 있습니다.

- 해당 옵션의 사용 가능 여부는 메뉴에서 해당 체크 박스가 활성화되어 있는지 여부로 확인할 수 있습니다.

<br>




### 2.2. 빌드 방법
1. 리포지토리를 다운로드 받습니다.

2. 다운 받은 리포지토리 디렉토리에 포함된 `PodoRenderer.slnx` 솔루션 파일을 더블 클릭합니다.

3. Visual Studio 상단의 구성(configuration)을 `Release` `x64`로 설정합니다.  

4. Visual Studio 상단에서 `빌드(B`의 `솔루션 빌드(Ctrl+Shift+B)`를 누릅니다.

5. `PodoRenderer/OutDir`에서 `PodoRendererRelease64.exe` 이름의 파일이 생성되었다면 빌드에 성공한 것입니다.

<br>




### 2.4. 실행 방법
1. 위 빌드를 통해서 생성한 `PodoRendererRelease64.exe`를 더블 클릭하여 실행합니다.

2. 로딩이 완료되면 `Click here to start` 버튼이 중앙 하단에 나타납니다. 이를 눌러 눌러 렌더링을 시작합니다.

3. 마우스 왼쪽 버튼을 누른 채로 마우스를 이동시키면 시야를 회전합니다. `WASD` 키보드로 카메라를 이동시킵니다.

4. 좌측 상단의 `Menu` 버튼을 누르면 메뉴와 함께 옵션이 나타납니다.

5. 종료하고 싶으면 메뉴의 `Exit` 버튼을 누르거나 `ALT+F4` 단축키를 누르면 됩니다. 



<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 3. 주요 기능
### 3.1. 렌더링 기능
기하 그리기는 아직 구현되지 않았고, 간단히 렌더 타겟의 색상을 진동시키는 루프만 작성되어있습니다.

<br>




### 3.2. 조작 기능
|입력|기능|
|---------------------|---------------------|
|마우스 좌클릭 + 이동 |시야 회전(미구현)    |
|창 끌기              |창 위치 이동         |
|창 모서리 끌기       |창 크기 변화         |
|키보드 `WASD`        |카메라 이동(미구현)  |
|키보드 `ESC`         |메뉴<->렌더링 간 전환|
|키보드 `ALT+ENTER`   |창모드 전환          |
|키보드 `ALT+F4`      |종료                 |

<br>




### 3.3. 옵션 기능
|제공 옵션|설정 값|
|---------------------|---------------------------------------------|
|창모드               |`창모드` or `테두리 없는 전체 창모드`        |
|VSync                |`Off` or `On`                                |
|Tearing              |`피처 지원 && VSync`에 따라 자동 적용        |
|HDR(미완)            |`Off` or `On`                                |
|레이 트레이싱(미구현)|`Off` or `On`                                |
|메쉬 셰이더(미구현)  |`Off` or `On`                                |
|GUI 크기             |`50%` or `75%` or `100%` or `125%` or `150%` |

- 옵션은 `작업 디렉토리`에 `SavedSettings.txt` 이름의 파일로 자동 저장되고 불러들여집니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 4. 측정 성능
### 4.1. 측정 환경
|||
|-------------------|---------------------------------------------------------------|    
|CPU                |i5-13600KF, 3500MHz, 14 코어, 20 논리 프로세서                 |
|GPU                |INN03D Geforece RTX 4070 Ti D6X 12GB X3                        |
|RAM                |32GB, DDR4, 3600MHz                                            |
|OS                 |Windows 11, 버전 25H2, 빌드 26200.8973                         |
|IDE                |Microsoft Visual Studio Community 2026 (64 - bit) 버전 18.8.2  |
|플랫폼 도구 집합   |v145 for Microsoft C++ Build Tools                             |
|컴파일러 버전      |x86용 Microsoft (R) C/C++ 최적화 컴파일러 버전 19.51.36252     |
|구성               |`Release x64`                                                  |

<br>





### 4.2. 측정 방식
PIX 사용법을 학습 중에 있습니다.

<br>




### 4.3. 측정 결과
PIX 사용법을 학습 중에 있습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 5. 구현 구조
### 5.1. 폴더
Frank Luna의 D3D12 입문 도서의 폴더 구조를 참고하여 다음과 같은 하위 폴더들을 두었습니다 [1].

- `Code`  
  : 헤더 파일 폴더(=`추가 포함 디렉토리`)와 소스 파일 폴더가 위치합니다.

- `External`  
  : 리포지토리 내부에 직접 포함된 외부 항목이 위치합니다.

- `IntDir` ( =`중간 디렉토리`)  
  : 컴파일 결과물이 위치합니다.

- `Model`  
  : 오브젝트, 애니메이션 파일들이 위치합니다.

- `OutDir` (=`출력 디렉토리`)  
  : 링크 결과물과, 런타임들이 위치합니다.

- `Shader`  
  : HLSL 셰이더 파일들이 위치합니다.

- `Texture`  
  : DDS 텍스처 파일들이 위치합니다.

<br>




### 5.2. 빌드
본 리포지토리는 Visual Studio의 `.vcxproj`를 통해 빌드 설정을 관리하고 있습니다.

일반적으로 다음과 같이 이루어지는 Visual Studio에서 응용 프로그램의 빌드 및 실행 방식을 따르고 있습니다.
| 단계 | 직접 입력 | 직접 입력 대상 | 간접 입력 | 간접 입력 대상 명시 | 간접 입력 대상 경로 명시 | 출력 | 출력 경로 |
|---|---|---|---|---|---|---|---|
| 전처리 + 컴파일 | `.cpp` | 프로젝트에 포함된 각 `.cpp` 파일 | `.h`, `.inl` | `#include <xxx.h>`, `#include "xxx.h"`| (`프로젝트 속성` > `C/C++` > `일반` > `추가 포함 디렉토리` > `편집`) | `.obj` | `중간 디렉토리` |
| 링크 | `.obj` | 컴파일된 `.obj` 파일들 | `.lib` | `#pragma comment(lib, "xxx.lib")` <br> or <br> (`프로젝트 속성` > `링커` > `입력` > `추가 종속성` > `편집`) | (`프로젝트 속성` > `링커` > `일반` > `추가 라이브러리 디렉토리` > `편집`) | `.exe` |  `출력 디렉토리` |
| 실행 | `.exe` | 링크된 `.exe` |  `.dll` | 링크 시점에 임포트 라이브러리를 링크 <br> (로드-타임 동적 링킹) <br> or <br> 실행 중 `LoadLibraryA(..)` 함수 사용 <br> (런-타임 동적 링킹) [2] | 해당 없음(`.dll`을 `.exe`의 디렉토리에 복사해주는 것이 일반적) | 프로세스 | 해당 없음 |

<br>

D3D12를 위해 사용하는 기본적인 빌드 대상은 다음과 같습니다 [3].

다만 후술할 NuGet 패키지 관리로 인해 파일의 경로와 세팅 방법은 아래 표와 다를 수 있습니다.
| 대상 | 관리 주체 | 내용물 | 목적 | 경로 | 세팅 방법 |
|---|---|---|---|---|---|
| Windows SDK | Visual Studio Installer | `.h`, `.inl`, `.lib` | 윈도우 앱 빌드에 필요한 헤더, 라이브러리 사용 |`C:\Program Files (x86)\Windows Kits` | 경로는 기본 설정되어 있음, <br> 무엇을 사용할지만 다음처럼 명시하면 됨 <br> `#include <d3d12.h>` <br> `#include <dxgi1_6.h>` <br> `#pragma comment(lib, "dxgi.lib")` <br> `#pragma comment(lib, "D3D12.lib")` <br> ... |
| DirectX Header | Microsoft Github Repository | `.h` | `d3dx12*.h` 헬퍼 구조체, 헬퍼 함수 사용 | https://github.com/microsoft/DirectX-Headers | 수동으로 다운로드 받아 프로젝트에 포함 |
| D3D12 Runtime | Windows | `.dll` | 응용 프로그램 구동에 필요한 런타임 사용 | `C:\Windows\System32` | 경로는 기본 설정되어 있음, <br> 임포트 라이브러리인 `D3D12.lib`을 통해 로드-타임 동적 링킹이 일어나므로 별도의 런-타임 동적 링킹이 필요 없음 |

<br>

본 리포지토리는 최신 D3D12 관련 헤더, 라이브러리, 런타임들을 리포지토리 내부에서 복원하여 사용할 수 있도록 NuGet 패키지 관리를 이용하고 있습니다.

Frank Luna의 D3D12 입문 도서에서 NuGet을 사용하는 것을 참고하였으며, 다만 해당 도서가 NuGet으로 관리하지 않고 직접 파일을 다운로드 받아 포함하던 대상들까지 모두 NuGet으로 복원되도록 확장하였습니다 [1].
| 대상 | 목적 | 파일 |
|---|---|---|
| DirectX 12 Agility SDK | 최신 D3D12 기능 사용 | `.h`, `.dll` |
| DirectXTK12 | DirectX12 툴 헤더, 라이브러리 사용 | `.h`, `.inl`, `.lib` |
| DirectX Shader Compiler (DXC) | HLSL 셰이더 파일 컴파일 | `.h`, `.lib`, `.dll` |

<br>

### 5.3. 초기화 로직
D3D12에 관련한 여러 COM 인터페이스를 얻고, 저장된 옵션을 불러오고, ImGui를 초기화하기 위해 아래와 같은 일련의 과정을 수행합니다.

```cpp
void InitApp()
{
	InitFactory();
	InitAdapterAndOutput();
	InitDevice();
	InitFence();
	InitFenceEvent();
	InitCommandQueue();
	InitCommandAllocator();
	InitCommandList();
	InitFormatSupport();
	InitHDRSwapChainSupport();
	InitSavedOptions();
	InitScreenMode();
	InitSwapChain();
	InitBackBufferInfo();
	InitViewPort();
	InitScissorRectangle();
	InitDepthStencilBuffer();
	InitDescriptorHeapRTV();
	InitDescriptorHeapDSV();
	InitDescriptorHeapCBVSRVUAV();
	InitRTV();
	InitDSV();
	InitCBVSRVUAV();
	InitImGui();
	InitTimers();

	//...
}
```
<br>




### 5.4. 업데이트 로직
일반적인 메시지 루프를 통하여 애플리케이션의 업데이트 로직을 수행합니다.

메시지 큐에 메시지가 있으면 이를 처리하는 것을 우선합니다.

그리고 GPU 연결이 변해 어댑터 인터페이스를 초기화해야 하거나, 창이 위치한 디스플레이가 바뀌어 아웃풋 인터페이스를 초기화해야 하는 경우라면 이를 처리하도록 합니다.

그리고 창모드, 화면 크기, HDR 옵션, GUI 크기 옵션이 변한 경우에 백버퍼 등 화면에 관련된 것들을 초기화하거나 재조정하도록 합니다.

위 경우들이 모두 아니라면 월드 업데이트나 렌더와 같은 작업을 수행합니다. 다만 월드 업데이트는 엔진이 메뉴 상태에 있다면 수행되지 않고, 렌더 업데이트는 창의 크기가 변화하는 도중엔 수행되지 않습니다.

이 두가지 업데이트가 모두 멈추었다면 스레드를 0.1초간 잠들게 하여 불필요한 연산을 방지합니다.

```cpp
int RunMessageLoop()
{
	MSG msg = { };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (NeedResetDxgiInterface() == true)
		{
			ResetDXGIInterface();
		}
		else if (NeedResetScreenSetting() == true)
		{
			ResetScreenSetting();
		}
		else
		{
			if (IsUpdateStopped() == true)
			{
				Sleep(100);
			}
			else
			{
				UpdateTimers();
				UpdateWorld();
				UpdateRender();
				UpdateCaption();
			}
		}
	}

	return (int)msg.wParam;
}
```
<br>




### 5.5. 조작 로직
일반적인 윈도우 메시지 처리 방식을 사용하고 있습니다.

이를 통해 마우스 회전(미구현), 키보드 `WASD` 이동(미구현), `ALT+ENTER` 창모드 전환 단축키, 창 모서리 크기 변화, 창 위치 변화, `ALT+F4` 종료 단축키를 처리합니다.

메뉴 전환 ESC 단축키는 윈도우 메시지를 직접 처리하지 않고 `ImGui::IsKeyPressed(..)`를 통해 처리하고 있습니다.

```cpp
LRESULT Podo::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  //...
  switch (uMsg)
  {
    case WM_MOUSEMOVE:      //...
    case WM_LBUTTONDOWN:    //...
    case WM_LBUTTONUP:      //...
    case WM_MOUSEWHEEL:     //...
    case WM_KEYDOWN:        //...
    case WM_SYSKEYDOWN:     //...
    case WM_SYSCHAR:        //...
    case WM_ENTERSIZEMOVE:  //...
    case WM_EXITSIZEMOVE:   //...
    case WM_SIZE:           //...
    case WM_MOVE:           //...
    case WM_DISPLAYCHANGE:  //...
    case WM_ACTIVATE:       //...
    case WM_CLOSE:          //...
    case WM_DESTROY:        //...
  }

	return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}
```
<br>




### 5.6. 종료 로직
오류를 예방하기 위해, GPU에 제출된 명령들이 모두 소진되고 나서 애플리케이션이 종료될 수 있도록 합니다.

```cpp
~Podo()
{
	ResetQueuedCommands();

	CloseFenceEvent();
	CloseImGui();
}
```
<br>




### 5.7. 자원
아직 구현하지 않음

<br>




### 5.8. 바인딩
아직 구현하지 않음

<br>




### 5.9. 셰이더
아직 구현하지 않음

<br>




### 5.10. 파이프라인 상태 객체
아직 구현하지 않음

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
  - 에셋 경량화             : 사전 생성 LOD, 뉴럴 셰이더
  - 파일 입출력 최적화      : DirectStorage
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
  - 셰이더 최적화           : 분기 수 조절, 로컬리티 개선, 뉴럴 셰이더 등

<br>

- **다중 PSO 렌더링**
  - 조형 PSO : 변위 매핑(지형, 수면), 스킨 애니메이션, 파티클
  - 조명 PSO : 블랜딩, 정적 환경 매핑, 동적 환경 매핑, 그림자 매핑, SSAO, 레이 트레이싱

<br>

- **다중 PSO 렌더링 최적화**
  - 비교          : 포워드 렌더링 vs 포워드+ 렌더링 vs 지연 렌더링(+다중 렌더 타겟)
  - 비교          : 네이티브 렌더링 vs VRS vs DirectSR
  - 비교          : 사전 생성 LOD vs 기하 셰이더 런타임 LOD vs 테셀레이션 런타임 LOD vs 메쉬 셰이더 런타임 LOD
  - 비교          : 단일 렌더 타겟 동적 입방체 그리기 vs 다중 렌더 타겟 어레이 동적 입방체 그리기(`WithoutGSEmulation`)
  - 비교          : 컴퓨트 셰이더 파티클 vs 메쉬 셰이더 파티클 vs Work Graphs
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
  본 렌더링 엔진은 DPI 설정값에 의한 윈도우의 자동 스케일링으로 화면이 훼손되지 않도록 DPI AWARENESS를 매니페스트에 명시하였습니다. 윈도우의 DPI 설정값은 GUI 크기에 반영하지 않고, 대신 옵션에서 GUI의 배율을 50%, 75%, 100%, 125%, 150% 중에서 선택할 수 있도록 하였습니다.

<br>

- **심화 렌더링 기법**  
  캐스케이드 셰도우 매핑, 복셀 광역 조명과 같은 심화 렌더링 기법은 추가 학습이 필요하기에 프로젝트 규모를 제한하고자 제외하였습니다.

<br>

- **안티 앨리어싱**  
  대중화된 QHD, UHD에 적합한 안티 앨리어싱 기법은 추가 학습이 필요하기에 프로젝트 규모를 제한하고자 제외하였습니다. 

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

"Timing Captures" (Microsoft Dev Blogs / 2026년 7월 방문)  
https://devblogs.microsoft.com/pix/timing-captures-new/

"WinPixEventRuntime" (Microsoft Dev Blogs / 2026년 7월 방문)  
https://devblogs.microsoft.com/pix/winpixeventruntime/

<br>