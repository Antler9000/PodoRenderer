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
- [9. 참고 자료](#9-참고-자료)

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
본 리포지토리는 Visual Studio의 `.vcxproj`를 통해 빌드 설정을 관리하고 있습니다.

일반적으로 Visual Studio에서 응용 프로그램의 빌드와 실행은 다음과 같이 이뤄집니다.
| 단계 | 직접 입력 | 직접 입력 대상 | 간접 입력 | 간접 입력 대상 명시 | 간접 입력 대상 경로 명시 | 출력 | 출력 경로 |
|---|---|---|---|---|---|---|---|
| 전처리 + 컴파일 | `.cpp` | 프로젝트에 포함된 각 `.cpp` 파일 | `.h`, `.inl` | `#include <xxx.h>`, `#include "xxx.h"`| (`프로젝트 속성` > `C/C++` > `일반` > `추가 포함 디렉토리` > `편집`) | `.obj` | `중간 디렉토리` |
| 링크 | `.obj` | 컴파일된 `.obj` 파일들 | `.lib` | `#pragma comment(lib, "xxx.lib")` <br> or <br> (`프로젝트 속성` > `링커` > `입력` > `추가 종속성` > `편집`) | (`프로젝트 속성` > `링커` > `일반` > `추가 라이브러리 디렉토리` > `편집`) | `.exe` |  `출력 디렉토리` |
| 실행 | `.exe` | 링크된 `.exe` |  `.dll` | 링크 시점에 임포트 라이브러리를 링크 <br> (로드-타임 동적 링킹) <br> or <br> 실행 중 `LoadLibraryA(..)` 함수 사용 <br> (런-타임 동적 링킹) [2] | 해당 없음(`.dll`을 `.exe`의 디렉토리에 복사해주는 것이 일반적) | 프로세스 | 해당 없음 |

<br>

D3D12 어플리케이션의 빌드와 실행에 필요한 대상들을 가장 간단히 나열하면 다음과 같습니다 [3].
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

    - dxgiformat.h는 두 경로의 파일 모두가 사용되었습니다. 다른 경로에 속한 헤더파일로부터의 각각 간접적으로 include되었기 때문으로 추측합니다.  
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
    - 변화가 적은 하위 로직을 담당하는 `dxgi.lib`와 `gdi32.lib`은 Visual Studio Installer로 관리되는 `Windows Kits`에 위치합니다. 다만 DirectXMath는 헤더파일(.h or .inl)으로만 구현되므로 라이브러리 파일이 존재하지 않습니다.
      - `C:\Program Files (x86)\Windows Kits\10\lib\10.0.26100.0\um\x64\gdi32.lib`
    
      - `C:\Program Files (x86)\Windows Kits\10\lib\10.0.26100.0\um\x64\dxgi.lib`

    - `D3D12.lib`은 dll을 로드하기 위한 임포트 라이브러리이기에 변화가 적어 `Windows Kits` 아래에 위치합니다.  
      - `C:\Program Files (x86)\Windows Kits\10\lib\10.0.26100.0\um\x64\D3D12.lib`

    - DirectXTK12는 NuGet에 의해 관리되므로 리포지토리 내부에 위치합니다.
      - `SodoSandbox\packages\directxtk12_desktop_win10.2026.5.8.1\build\native\..\..\native\lib\x64\Debug\DirectXTK12.lib`

    - DXC는 NuGet에 의해 관리되므로 이에 속한 `dxcompiler.lib`은 리포지토리 내에 위치하며 관리됩니다. 다만 레거시인 `d3dcompiler.lib`은 NuGet에 의해 관리되지 않기에 `Windows Kits` 디렉토리 아래에 위치합니다.
      - `SodoSandbox\packages\Microsoft.Direct3D.DXC.1.9.2602.24\build\native\lib\x64\dxcompiler.lib`

      - `C:\Program Files (x86)\Windows Kits\10\lib\10.0.26100.0\um\x64\d3dcompiler.lib`

<br>

- 실행 의존
  - 확인 방법
    1. 상단의 `디버그` > `디버깅 시작`
    2. 상단의 `디버그` > `창` > `모듈`

  - 확인된 목록
    - 변화가 적은 gdi32와 dxgi는 NuGet이 관리하지 않습니다. 그렇기에 해당 런타임들은 윈도우 업데이트로 관리되는 `System32` 디렉토리에 위치합니다.  
      - `C:\Windows\System32\gdi32.dll`

      - `C:\Windows\System32\gdi32full.dll`

      - `C:\Windows\System32\dxgi.dll`

      - `C:\Windows\System32\DXGIDebug.dll`

      - `C:\Windows\System32\DXCore.dll`

      - `C:\Windows\System32\directxdatabasehelper.dll`

    - `D3D12.dll`은 핵심 로직을 수행하지 않고 얇은 로더 역할을 수행하므로 NuGet에 의해 관리되지 않습니다. 그러나 핵심 로직이 담긴 `D3D12Core.dll`은 NuGet에 의해 관리되기에 리포지토리 내부에 복원됩니다 [4].  
      - `C:\Windows\System32\D3D12.dll`

      - `SodoSandbox\OutDir\D3D12\D3D12Core.dll`

      - `SodoSandbox\OutDir\D3D12\D3D12SDKLayers.dll`

    - DXC는 NuGet에 의해 관리되므로 `dxcompiler.dll`은 리포지토리 내에 위치합니다. 이와 달리, 레거시인 `D3DCompiler_47.dll`는 NuGet에 의해 관리되지 않기에 `System32` 디렉토리에 위치합니다.  
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
### 6.1. 빌드
- 없음

<br>




### 6.2. 윈도우 창
- 없음

<br>




### 6.3. 그래픽
- **시각적 기능**
  - 참고 자료 읽기
  - 루트 서명, 파이프라인 상태 객체 작성하기
  - 기초적인 정점 셰이더, 픽셀 셰이더 작성하기
  - 조명 효과 작성하기
  - 텍스처 맵핑 작성하기
  - 노말 맵핑 작성하기
  - 그림자 맵핑 작성하기
  - SSAO 작성하기
  - 이펙트 작성하기
  - 레이 트레이싱 옵션 작성하기
  
<br>

- **성능 개선**
  - 참고 자료 읽기
  - PIX 툴 기능 접하기
  - CPU-GPU 간 병렬성 개선
  - 파이프라인 상태 객체 변경 횟수 줄이기
  - 루트 서명 크기 줄이기
  - 루트 인자 변경 횟수 줄이기
  - 그리기 명령 횟수 줄이기
  - 절두체 선별 도입하기
  - 월드 자원 관리 도입하기
  - 메시 셰이딩 옵션 작성하기
  - 멀티 스레딩 도입하기

<br>




### 6.4. 디스플레이
- **SRGB 감마 인코딩**
  - SDR 렌더링에서 자원 포맷 `DXGI_FORMAT_R8G8B8A8_UNORM`과 별도로 RTV의 포맷을 `DXGI_FORMAT_R8G8B8A8_UNORM_SRGB`로 지정하여 자동적으로 감마 디코딩과 인코딩이 일어나도록 하기

<br>

- **제시 지연 개선**
  - 참고 자료 읽기
  - 프레임 자원과 `SetMaximumFrameLatency` 인자값과 대기 시점 결정하기
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




### 6.5. 게임 로직
- **게임 시작 로딩 기능**
  - 자원 로딩이 끝나면 게임으로 들어가는 버튼이 활성화되도록 하기
  - 로비로 향하는 로딩은 자원 정리가 끝나면 버튼 없이 자동 수행되도록 하기

<br>

- **세이브, 로드 기능**
  - 게임 상태를 저장할 수 있도록 하기
  - 게임 상태를 복원할 수 있도록 하기

<br>

- **환경 요소**
  - 참고 자료 읽기
  - 지형 요소 도입하기
  - 수면 요소 도입하기
  - 초목 요소 도입하기
  - 건물 요소 도입하기

<br>

- **객체 요소**
  - 객체 정보를 관리하고 추적하는 테이블 도입하기

<br>

- **객체 선택 기능**
  - 참고 자료 읽기
  - 화면을 클릭 객체 선택 기능 작성하기
  - 화면 드래그 객체 선택 기능 작성하기
  - 선택 상태용 커서 변경 작성하기
  - 선택된 객체 강조 효과 작성하기

<br>

- **객체 이동 기능**
  - 참고 자료 읽기
  - 바닥 및 장애물 판정 로직 작성하기
  - 이동 및 회전 로직 작성하기
  - 이동 경로 탐색 로직 작성하기
  - 이동 상태용 커서 변경 작성하기
  - 이동 애니메이션 작성하기

<br>

- **객체 전투 기능**
  - 적 인식 기능 작성하기
  - 자동 접근 및 공격 기능 작성하기
  - 유닛 선택을 통한 공격 명령 기능 작성하기
  - 공격 상태용 커서 변경 작성하기
  - 공격 및 피격 애니메이션 작성하기

<br>

- **객체 획득 기능**
  - 객체를 들어서 옮길 수 있도록 하기
  - 객체를 인벤토리에 넣고 꺼낼 수 있도록 하기
  - 획득 상태용 커서 변경 작성하기
  - 저장된 객체를 볼 수 있는 GUI 제공하기

<br>

- **객체 기타 기능**
  - 객체 변환, 합성, 부패 기능 제공하기
  - 대화, 의뢰, 거래 기능 제공하기

<br>

- **이벤트 요소**
  - 랜덤 인카우터, 사건과 같은 이벤트 요소 제공하기

<br>

- **게임 사운드**
  - GUI 반응 사운드 제공하기
  - 인게임 사운드 제공하기

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 7. 구현 제외
- **CMAKE 기반 빌드 구성**  
  Win32, D3D12를 이용한 윈도우 타겟 어플리케이션이라는 점, 1인 프로젝트라는 점을 고려하여, 별도의 CMAKE를 도입하지 않고 Visual Studio의 `.vcxproj`를 통해 빌드 설정을 관리하고 있습니다.

<br>

- **VCPKG 기반 의존성 관리**  
  마이크로소프트는 2026년 5월 이후로 DirectXTK12을 사용하려면 NuGet 패키지 대신 VCPKG를 이용하길 권장하고 있으나, 본 리포지토리는 툴 헤더와 라이브러리의 최신 기능이 현재 필요하지는 않으므로 일단 다른 대상과 함께 NuGet으로 통합 관리하고자 합니다. 현재 DirectXTK12가 참조하는 `d3d12.h`의 버전이 NuGet으로 관리되는 Agility SDK에 담긴 최신 `d3d12.h`의 버전과 달라져 문제가 발생할 수 있음을 인지하고 있지만, 새로운 의존성 관리 방식을 추가로 도입하는 것은 복잡성을 높이므로 선제적으로 VCPKG를 도입하여 예방하기보다는 지속적인 리포지토리 관리 중 문제가 발생하면 조치하려고 합니다.

<br>

- **디바이스 소실 대응**  
  게임 중 디바이스가 사라지는 경우는 흔치 않으며, 이를 감지하고 우회하는 로직 또한 간단하지 않기에 구현하지 않았습니다.

<br>

- **자체 GUI 렌더링 기능**  
  자체 GUI가 있으면 게임의 분위기를 더 잘 반영할 수 있겠지만, GUI를 직접 구현하는 것은 큰 시간이 필요할 것 같아 Dear ImGui를 통해 구현하기로 하였습니다. 다만 마우스가 아닌 키보드 조작에만 의존하는 폴아웃의 핍보이와 같은 인게임 GUI는 상대적으로 구현이 쉽고 동시에 몰입도를 살릴 수 있을 것 같아, 먼 시점에 자체 인게임 GUI를 구현하는 것을 고려하고 있습니다.

<br>

- **자체 ImGui 힙 할당자**  
  최신 ImGui는 SRV를 1 개만 사용하지 않고 여러 개 사용하기에, 서술자 힙의 일부를 할양하고 또 해제받는 할당자를 응용프로그램 작성자가 직접 구현해주어야 합니다. 다만 ImGui가 사용하는 서술자 개수가 많지 않기에 정교한 할당자를 직접 구현할 필요는 없다고 판단하여 Dear ImGui의 내부 예제에 실린 간단한 할당자를 일부 수정하여 사용하고 있습니다.

<br>

- **DPI 설정값 반영**  
  사용자는 화면에 나타나는 논리적인 요소들의 배율을 뜻하는 DPI를 윈도우의 디스플레이 설정을 통해 지정할 수 있습니다. 유저가 DPI 설정 값을 바꾸거나 이미 다른 값이 설정된 디스플레이로 게임 창이 이동하게 될 시 게임의 GUI 크기에 이를 반영하는 것이 좋을 수 있으나, GUI 크기를 명시적으로 설정할 수 있도록 하는 것이 더 좋으리라 생각하여 이를 제외하였습니다. 본 게임은 DPI 설정값에 의한 윈도우의 자동 스케일링이 일어나지않도록 DPI AWARENESS를 메니페스트에 명시하였습니다. 게임 로직에서는 윈도우의 DPI 설정값을 반영하는 로직을 작성하지 않고, 대신 게임 옵션에서 GUI의 물리적 픽셀 배율을 50%, 75%, 100%, 125%, 150% 중에서 선택할 수 있도록 하고 있습니다.

<br>

- **WM_INPUT 메세지 처리**  
  `WM_INPUT` 메세지를 이용하면 윈도우에서 추상화한 마우스 움직임이 아닌, 마우스의 Raw 인풋을 그대로 받을 수 있어 마우스 인풋 처리 과정에서 정보 손실을 줄이고 윈도우의 마우스 가속 설정에 영향을 받지 않도록 할 수 있습니다. 그러나 창 모드 상태에서 게임 속 커서의 이동 속도와 외부에서의 윈도우 커서의 속도가 일관성을 가질 수 있도록 함과 동시에 간단히 구현할 수 있도록 WM_INPUT을 처리하지 않고 `WM_MOUSEMOVE`와 같은 기초적인 메세지를 처리하도록 구현하였습니다.

<br>

- **자체 커서 렌더링 기능**  
  간단한 구현을 위해, 자체 커서를 렌더링하는 과정을 두지 않고 윈도우 커서를 변경하는 방식을 사용할 예정입니다. 윈도우 커서도 여러 게임 상태에 맞게 변경이 가능하고, 타 오버레이와 달리 Independent Flip과 같은 제시 최적화를 방해하지 않기에 인 게임 커서로 사용하여도 무리가 없다고 판단하였습니다.

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




### 8.4. PIX Event Runtime
- 목적
  - PIX 캡처

- 사용 방식
  - NuGet 패키지 관리 (WinPixEventRuntime)
  
- 복원 위치
  - `SodoSandbox\packages\WinPixEventRuntime.<버전명>`

- 라이선스 종류
  - MIT License

- 라이선스 위치
  - `SodoSandbox\packages\WinPixEventRuntime.<버전명>\license.txt`

<br>




### 8.5 Dear ImGui
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