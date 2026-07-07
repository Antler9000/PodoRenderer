# SodoSandbox
D3D12, Win32, ImGui를 이용하여 구현 중인 샌드박스 게임 리포지토리입니다.

윈도우 3D 게임 형태를 갖추기 위한 탐색 구현 과정에 있습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 목차
- [1. 데모 영상](#1-데모-영상)
- [2. 실행 방법](#2-실행-방법)
- [3. 주요 기능](#3-주요-기능)
- [4. 구현 구조](#4-구현-구조)
- [5. 성능 측정](#5-성능-측정)
- [6. 구현 예정](#6-구현-예정)
- [7. 구현 제외](#7-구현-제외)
- [8. 외부 항목](#8-외부-항목)
- [9. 인용 참고](#9-인용-참고)
- [10. 구현 참고](#10-구현-참고)

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 1. 데모 영상
### 1.1. 데모 영상
아직 구현하지 않음

<br>




### 1.2. 데모 스크린샷
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




### 2.3. 설정 방법
아직 구현하지 않음

<br>




### 2.4. 조작 방법
아직 구현하지 않음

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 3. 주요 기능
### 3.1. 조명 기능
아직 구현하지 않음

<br>




### 3.2. 소리 기능
아직 구현하지 않음

<br>




### 3.3. 초목 기능
아직 구현하지 않음

<br>




### 3.4 건물 기능
아직 구현하지 않음

<br>




### 3.5. 인물 기능
아직 구현하지 않음

<br>




### 3.6. 플레이 기능
아직 구현하지 않음

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 4. 구현 구조
### 4.1. 폴더 구성
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




### 4.2. 빌드 관리
일단 별도의 빌드 시스템 없이 Visual Studio에서 직접 빌드를 관리하고 있습니다.

일반적으로 Visual Studio에서 응용 프로그램의 빌드와 실행은 다음과 같이 이뤄집니다.
| 단계 | 직접 입력 | 직접 입력 대상 | 간접 입력 | 간접 입력 대상 명시 | 간접 입력 대상 경로 명시 | 출력 | 출력 경로 |
|---|---|---|---|---|---|---|---|
| 전처리 + 컴파일 | `.cpp` | 프로젝트에 포함된 각 `.cpp` 파일들 | `.h`, `.inl` | `#include <xxx.h>`, `#include "xxx.h"`| (`프로젝트 속성` > `C/C++` > `일반` > `추가 포함 디렉토리` > `편집`) | `.obj` | `중간 디렉토리` |
| 링크 | `.obj` | 컴파일된 `.obj` 파일들 | `.lib` | `#pragma comment(lib, "xxx.lib")` <br> or <br> (`프로젝트 속성` > `링커` > `입력` > `추가 종속성` > `편집`) | (`프로젝트 속성` > `링커` > `일반` > `추가 라이브러리 디렉토리` > `편집`) | `.exe` |  `출력 디렉토리` |
| 실행 | `.exe` | 링크된 `.exe` |  `.dll` | 링크 시점에 임포트 라이브러리를 링크 <br> (로드-타임 동적 링킹) <br> or <br> 실행 중 `LoadLibraryA(..)` 함수 사용 <br> (런-타임 동적 링킹) [2] | 해당 없음(`.dll`을 `.exe`의 디렉토리에 복사해주는 것이 일반적) | 프로세스 | 해당 없음 |

<br>

D3D12에 관련된 간접 입력 대상들을 가장 간단히 세팅한다면 이용하는 대상은 주로 다음과 같습니다.
| 대상 | 관리 주체 | 내용물 | 목적 | 경로 | 세팅 방법 |
|---|---|---|---|---|---|
| Windows SDK | Visual Studio Installer | `.h`, `.inl`, `.lib` | 윈도우 앱 빌드에 필요한 헤더, 라이브러리 사용 |`C:\Program Files (x86)\Windows Kits` | 경로는 기본 설정되어 있음, <br> 무엇을 사용할지만 다음처럼 명시하면 됨 <br> `#include <d3d12.h>` <br> `#include <dxgi1_6.h>` <br> `#pragma comment(lib, "dxgi.lib")` <br> `#pragma comment(lib, "D3D12.lib")` <br> ... |
| DirectX Header | Microsoft Github Repository | `.h` | `d3dx12*.h` 헬퍼 구조체, 헬퍼 함수 사용 | https://github.com/microsoft/DirectX-Headers | 수동으로 다운로드 받아 프로젝트에 포함 |
| D3D12 Runtime | Windows | `.dll` | 응용 프로그램 구동에 필요한 런타임 사용 | `C:\Windows\System32` | 경로는 기본 설정되어 있음, <br> 임포트 라이브러리인 `D3D12.lib`을 통해 로드-타임 동적 링킹이 일어나므로 별도의 런-타임 동적 링킹 또한 필요 없음 |

<br>

위 방법에 더하여, Frank Luna의 D3D12 입문 도서가 NuGet으로 최신 헤더, 라이브러리, 런타임을 배포된 리포지토리 내부에서 복원되도록 한 방식을 참고하여 사용했습니다 [1]. 다만 본 리포지토리에서는 해당 도서가 NuGet으로 관리하지 않고 직접 파일을 포함하던 대상들까지 모두 NuGet으로 복원되도록 확장 적용하였습니다.
| 대상 | 목적 | 파일 |
|---|---|---|
| DirectX 12 Agility SDK | 최신 D3D12 기능 사용 | `.h`, `.dll` |
| DirectXTK12 | 최신 DirectX12 툴 사용 | `.h`, `.inl`, `.dll` |
| DirectX Shader Compiler (DXC) | HLSL 셰이더 파일 컴파일 | `.h`, `.lib`, `.dll` |

<br>

임시 코드를 `main.cpp`에 삽입하여 확인한 결과, 본 리포지토리 환경에서 빌드에 사용되는 DirectX 관련 파일들의 경로는 다음과 같습니다.

- 전처리 및 컴파일 입력
  - 확인 방법
    1. `프로젝트 속성` > `C/C++` > `포함 표시` > `예(/showIncludes)` 설정
    2. 상단의 `빌드` > `솔루션 빌드` > 하단의 출력창의 `출력 보기 선택`을 `빌드`로 선택

  - 확인된 목록
    - 변화가 적은 dxgi와 DirectXMath는 NuGet의 관리 대상이 아니기에 이들에 관련된 헤더 파일들은 Visual Studio Installer가 관리하는 Windows Kits에 위치합니다.  
      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\um\DirectXMath.h`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\um\DirectXMathConvert.inl`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\um\DirectXMathVector.inl`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\um\DirectXMathMatrix.inl`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\um\DirectXMathMisc.inl`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\um\DirectXPackedVector.h`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\um\DirectXPackedVector.inl`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\dxgi.h`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\dxgicommon.h`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\dxgi1_2.h`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\dxgi1_3.h`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\dxgi1_4.h`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\dxgi1_5.h`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\dxgi1_6.h`

      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\dxgitype.h`

    - 특이하게 dxgiformat.h는 두 경로의 파일 모두가 사용되었습니다. 이는, 다른 경로에 속한 헤더파일로부터의 각각 간접적으로 include되었기 때문으로 추측합니다.  
      - `C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\dxgiformat.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\dxgiformat.h`

    - DirectX Agility SDK, DirectXTK12, DXC는 NuGet에 의해 관리되기에 d3d12, d3dx12, SimpleMath, dxcapi 관련 헤더파일들은 본 리포지토리의 아래에 복원됩니다.  
      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3d12.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dcommon.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3d12sdklayers.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_barriers.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_core.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_default.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_pipeline_state_stream.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_render_pass.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_resource_helpers.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_property_format_table.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_root_signature.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_state_object.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_check_feature_support.h`

      - `SodoSandbox\packages\directxtk12_desktop_win10.2026.5.8.1\include\SimpleMath.h`

      - `SodoSandbox\packages\directxtk12_desktop_win10.2026.5.8.1\include\SimpleMath.inl`

      - `SodoSandbox\packages\directxtk12_desktop_win10.2026.5.8.1\include\GraphicsMemory.h`

      - `SodoSandbox\packages\Microsoft.Direct3D.DXC.1.9.2602.24\build\native\include\dxcapi.h`

<br>

- 링크 입력
  - 확인 방법
    1. `프로젝트 속성` > `링커` > `명령줄` > `추가 옵션` > `/VERBOSE:LIB` 입력
    2. 상단의 `빌드` > `솔루션 빌드` > 하단의 출력창의 `출력 보기 선택`을 `빌드`로 선택

  - 확인된 목록
    - 변화가 적은 하위 로직을 담당하는 dxgi.lib와 gdi32.lib은 Windows Kits에 위치합니다. 다만 DirectXMath는 헤더파일(.h or .inl)으로만 구현되므로 라이브러리 파일이 존재하지 않습니다.
      - `C:\Program Files (x86)\Windows Kits\10\lib\10.0.26100.0\um\x64\gdi32.lib`
    
      - `C:\Program Files (x86)\Windows Kits\10\lib\10.0.26100.0\um\x64\dxgi.lib`

    - D3D12.lib은 dll을 로드하기 위한 임포트 라이브러리이기에 변화가 적어 Visual Studio Installer가 관리하는 Windows Kits 아래에 위치합니다.  
      - `C:\Program Files (x86)\Windows Kits\10\lib\10.0.26100.0\um\x64\D3D12.lib`

    - DirectXTK12는 NuGet에 의해 관리되므로, 리포지토리 내부에 위치합니다.
      - `SodoSandbox\packages\directxtk12_desktop_win10.2026.5.8.1\build\native\..\..\native\lib\x64\Debug\DirectXTK12.lib`

    - DXC는 NuGet에 의해 관리되므로, dxcompiler.lib은 리포지토리 내에 위치하며 관리됩니다. 다만, 레거시인 d3dcompiler.lib은 파악하지 못한 간접적인 경로로 링킹된 것으로 추측합니다.  
      - `SodoSandbox\packages\Microsoft.Direct3D.DXC.1.9.2602.24\build\native\lib\x64\dxcompiler.lib`

      - `C:\Program Files (x86)\Windows Kits\10\lib\10.0.26100.0\um\x64\d3dcompiler.lib`

<br>

- 실행 의존
  - 확인 방법
    1. 상단의 `디버그` > `디버깅 시작`
    2. 상단의 `디버그` > `창` > `모듈`

  - 확인된 목록
    - 변화가 적은 gdi32와 dxgi는 NuGet이 관리하지 않습니다. 그렇기에 윈도우가 관리하는 System32에 런타임이 위치합니다.  
      - `C:\Windows\System32\gdi32.dll`

      - `C:\Windows\System32\gdi32full.dll`

      - `C:\Windows\System32\dxgi.dll`

      - `C:\Windows\System32\DXGIDebug.dll`

      - `C:\Windows\System32\DXCore.dll`

      - `C:\Windows\System32\directxdatabasehelper.dll`

    - D3D12.dll은 핵심 로직을 수행하지 않고, 얇은 로더 역할을 수행하므로 NuGet에 의해 관리되지 않습니다. 그러나 핵심 로직이 담긴 D3D12Core.dll은 NuGet에 의해 관리되기에 리포지토리 내부에 복원됩니다.  
      - `C:\Windows\System32\D3D12.dll`

      - `SodoSandbox\OutDir\D3D12\D3D12Core.dll`

      - `SodoSandbox\OutDir\D3D12\D3D12SDKLayers.dll`

    - DXC는 NuGet에 의해 관리되므로 dxcompiler.dll은 리포지토리 내에 위치하고 레거시인 D3DCompiler_47.dll는 NuGet에 의해 관리되지 않기에 System32 아래에 위치합니다.  
      - `SodoSandbox\OutDir\dxcompiler.dll`

      - `C:\Windows\System32\D3DCompiler_47.dll`

<br>




### 4.3. 입력 처리
일반적인 윈도우 메시지 처리 방식을 사용하고 있습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 5. 성능 측정
### 5.1. 측정 환경
아직 구현하지 않음

<br>




### 5.2. 측정 방식
아직 구현하지 않음

<br>




### 5.3. 측정 결과
아직 구현하지 않음

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 6. 구현 예정
- **게임 상태 기억 기능**
  - 게임 상태를 스택에 저장하도록 하여 게임 상태의 수를 줄이기
  - ESC 키를 눌러 이전 상태로 돌아갈 수 있도록 하기
  - ALT+F4를 눌렀을 때 저장이 필요한 상태라면, 종료 전 저장이 필요함을 알리는 상태로 가도록 하기

<br>

- **백그라운드 실행 기능**
  - 현재 주 선택 창에서 벗어나거나 작업바로 내려가도 게임 업데이트가 일어날 수 있도록 하기
  - 창이 보이지 않는 경우엔 렌더링 루프를 멈추도록 구현하기

<br>

- **윈도우 DPI 설정 대응**
  - 참고 자료 읽기
  - 창이 위치한 모니터에 대한 윈도우의 DPI 설정에 어떻게 대응할지 결정하기

<br>

- **3D 도형 그리기 기능**
  - 루트 서명, 파이프라인 상태 객체 등 작성하기
  - 간단한 정점 셰이더, 픽셀 셰이더 작성하기

<br>

- **로딩 기능**
  - 크리틱컬한 과정 중에는 m_gameNeedAlive를 true로 해놓고, 해당 과정이 끝나면 false로 되돌리기
  - 자원 로딩이 끝나면 게임으로 들어가는 버튼이 활성화되도록 하기
  - 로비로 향하는 로딩은 자원 정리가 끝나면 버튼 없이 자동 수행되도록 하기

<br>

- **게임 저장 기능**
  - 게임 상태가 갱신된지 여부를 m_gameNeedSave 변수에 반영하기
  - 게임 저장 및 복구 로직과 GUI 작성하기

<br>

- **SRGB 감마 인코딩**
  - SDR 렌더링에서 자원 포맷 `DXGI_FORMAT_R8G8B8A8_UNORM`과 별도로 RTV의 포맷을 `DXGI_FORMAT_R8G8B8A8_UNORM_SRGB`로 지정하여 자동적으로 감마 디코딩과 인코딩이 일어나도록 하기
  - 전후 색감 확인하기

<br>

- **제시 방법 개선**
  - 참고 자료 읽기
  - 업로드 용 버퍼 개수와 `SetMaximumFrameLatency` 인자값을 결정하기
  - PresentMon으로 전후의 제시 지연 측정하기

<br>

- **HDR 기능, 렌더 해상도 조절 기능**
  - 참고 자료 읽기
  - 렌더 버퍼의 톤 매핑, 색역 매핑 HLSL 작성하기
  - GUI 버퍼의 기준 밝기 조정 작성하기
  - 위 과정과 함께 둘을 합성하여 백버퍼에 저장하는 패스 구현하기
  - 백버퍼, GUI 해상도와 별개로 렌더 해상도를 조절할 수 있도록 하기
  - 용량이 더 작은 `DXGI_FORMAT_R10G10B10A2_UNORM`과 이에 대응되는 색공간 `DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020`을 도입하기 위해 색역 매핑을 변경하고 PQ 전달 함수 작성하기

<br>

- **멀티 스레딩**
  - 참고 자료 읽기
  - 부하가 크고 선형 의존성이 적은 CPU 작업을 스레드 병렬화하기

<br>

- **메모리 관리**
  - 참고 자료 읽기
  - 힙과 자원의 관리를 구현하기

<br>

- **빌드 설명 개선**
  - 참고 자료 읽기
  - 리드미 속 설명과 인용 다듬기

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 7. 구현 제외
- **디바이스 소실 대응**  
  게임 실행 중 사용중이던 디바이스가 사라지는 경우는 흔치 않고 대응하기도 힘드므로, 이를 식별하여 복구하는 로직은 구현하지 않았습니다.

<br>

- **자체 GUI 기능**  
  자체 GUI가 있으면 게임의 분위기를 더 잘 반영할 수 있겠지만, GUI를 직접 구현하는 것은 큰 시간이 필요할 것 같아 Dear ImGui를 통해 구현하기로 하였습니다. 다만 마우스가 아닌 키보드 조작에만 의존하는 폴아웃의 핍보이와 같은 인게임 GUI는 상대적으로 구현 난이도가 적음과 동시에 몰입도를 살릴 수 있으리라 예상해 구현을 고려하고 있습니다.

<br>

- **자체 ImGui 힙 할당자**  
  최신 ImGui는 SRV를 1개만 사용하지 않고 여러개 사용하기에, 서술자힙의 일부를 할양하고 또 해제받는 할당자를 직접 구현하여야 합니다. 다만 ImGui가 사용하는 서술자 개수가 많지 않기에 정교한 할당자를 직접 구현할 필요는 없다고 판단하여 Dear ImGui의 내부 예제에 실린 간단한 할당자를 일부 수정하여 사용하고 있습니다.

<br>

- **WM_INPUT 처리**  
  `WM_INPUT`을 사용하면 윈도우에서 인식한 픽셀 변화값이 아니라 마우스의 물리적인 입력값을 바로 사용할 수 있어, 픽셀 경계로 인한 양자화나 윈도우의 마우스 속도 설정에 영향을 받지 않을 수 있으나, 간단한 구현을 위해 `WM_MOUSEMOVE`와 같은 기초적인 메세지의 처리만을 작성하였습니다.

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
  - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.<버전명>`

- 라이선스 종류
  - MICROSOFT SOFTWARE LICENSE
  - MIT License

- 라이선스 위치
  - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.<버전명>\LICENSE.txt`
  - `SodoSandbox\packages\Microsoft.Direct3D.D3D12.<버전명>\LICENSE-CODE.txt`

<br>




### 8.2. DirectX Tool Kit (DirectXTK12)
- 목적
  - Direct3D 12 유틸리티 라이브러리 사용

- 사용 방식
  - NuGet 패키지 관리 (directxtk12_desktop_win10)

- 복원 위치
  - `SodoSandbox\packages\directxtk12_desktop_win.<버전명>`

- 라이선스 종류
  - MIT License

- 라이선스 위치
  - `SodoSandbox\packages\directxtk12_desktop_win10.<버전명>\docs\README.md` 내부 간접 링크
  - `https://github.com/microsoft/DirectXTK12/blob/main/LICENSE`

<br>




### 8.3. DirectX Shader Compiler (DXC)
- 목적
  - HLSL 셰이더 컴파일

- 사용 방식
  - NuGet 패키지 관리 (Microsoft.Direct3D.DXC)
  
- 복원 위치
  - `SodoSandbox\packages\Microsoft.Direct3D.DXC.<버전명>`

- 라이선스 종류
  - MIT License
  - LLVM Release License
  - MICROSOFT SOFTWARE LICENSE

- 라이선스 위치
  - `SodoSandbox\packages\Microsoft.Direct3D.DXC.<버전명>\LICENCE-MIT.txt`
  - `SodoSandbox\packages\Microsoft.Direct3D.DXC.<버전명>\LICENSE-LLVM.txt`
  - `SodoSandbox\packages\Microsoft.Direct3D.DXC.<버전명>\LICENSE-MS.txt`

<br>




### 8.4 Dear ImGui
- 목적
  - 인게임 GUI 제공

- 사용 방식
  - 내부 직접 포함(`SodoSandbox\External\imgui`)
  - 예제 수정 사용(`SodoSandbox\Code\Header\Alloc.h`)

- 원본 리포지토리
  - ocornut/imgui  
    `https://github.com/ocornut/imgui`

- 라이선스 종류
  - MIT License

- 라이선스 위치
  - `SodoSandbox\External\imgui\LICENSE.txt`

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 9. 인용 참고
[1] "Introduction To 3D Game Programming With DirectX 12 Second Edition" (Frank D. Luna 지음 / Mercury Learning And Information 출판 / 2025년 발행)  

[2] "Dynamic-Link Libraries (Dynamic-Link Libraries)" (Microsoft Learn / 2026년 6월 재방문)  
https://learn.microsoft.com/en-us/windows/win32/dlls/dynamic-link-libraries

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 10. 구현 참고
"Get Started with Win32 and C++" (Microsoft Learn / 2026년 6월 재방문)  
https://learn.microsoft.com/en-us/windows/win32/learnwin32/learn-to-program-for-windows

"ComPtr" (microsoft / 2026년 7월 재방문)  
https://github.com/Microsoft/DirectXTK/wiki/ComPtr

"The Care and Feeding of Modern Swap Chains" (Chuck Walbourn / 2026년 7월 재방문)  
https://walbourn.github.io/care-and-feeding-of-modern-swapchains/  
https://walbourn.github.io/care-and-feeding-of-modern-swap-chains-2/  
https://walbourn.github.io/care-and-feeding-of-modern-swap-chains-3/

"PresentMon" (GameTechDev / 2026년 7월 재방문)  
https://github.com/GameTechDev/PresentMon

<br>