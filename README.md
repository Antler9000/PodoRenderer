# PodoRenderer
"Introduction To 3D Game Programming With DirectX 12" 책의 개념을 참고해 설계 및 구현 중인 렌더링 엔진 리포지토리입니다 [1].

대규모 월드의 부하를 견딜 수 있도록 하는 것을 목표로 하고 있습니다.

현재 최소한의 렌더링 엔진 형태를 갖추기 위한 탐색 구현 과정에 있습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 목차
- [1. 데모 영상](#1-데모-영상)
- [2. 실행 방법](#2-실행-방법)
- [3. 주요 기능](#3-주요-기능)
- [4. 구현 구조](#4-구현-구조)
- [5. 측정 성능](#5-측정-성능)
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




### 2.4. 실행 방법
아직 구현하지 않음

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 3. 주요 기능
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

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\dxgiformat.h`

    - DirectX Agility SDK, DirectXTK12, DXC는 NuGet에 의해 관리되기에 d3d12, d3dx12, SimpleMath, dxcapi 관련 헤더파일들은 본 리포지토리의 아래에 복원됩니다.  
      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3d12.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dcommon.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3d12sdklayers.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_barriers.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_core.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_default.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_pipeline_state_stream.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_render_pass.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_resource_helpers.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_property_format_table.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_root_signature.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_state_object.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.D3D12.1.619.3\build\native\include\d3dx12\d3dx12_check_feature_support.h`

      - `PodoRenderer\packages\directxtk12_desktop_win10.2026.5.8.1\include\SimpleMath.h`

      - `PodoRenderer\packages\directxtk12_desktop_win10.2026.5.8.1\include\SimpleMath.inl`

      - `PodoRenderer\packages\directxtk12_desktop_win10.2026.5.8.1\include\GraphicsMemory.h`

      - `PodoRenderer\packages\Microsoft.Direct3D.DXC.1.9.2602.24\build\native\include\dxcapi.h`

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
      - `PodoRenderer\packages\directxtk12_desktop_win10.2026.5.8.1\build\native\..\..\native\lib\x64\Debug\DirectXTK12.lib`

    - DXC는 NuGet에 의해 관리되므로 이에 속한 `dxcompiler.lib`은 리포지토리 내에 위치하며 관리됩니다. 다만 레거시인 `d3dcompiler.lib`은 NuGet에 의해 관리되지 않기에 `Windows Kits` 디렉토리 아래에 위치합니다.
      - `PodoRenderer\packages\Microsoft.Direct3D.DXC.1.9.2602.24\build\native\lib\x64\dxcompiler.lib`

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

      - `PodoRenderer\OutDir\D3D12\D3D12Core.dll`

      - `PodoRenderer\OutDir\D3D12\D3D12SDKLayers.dll`

    - DXC는 NuGet에 의해 관리되므로 `dxcompiler.dll`은 리포지토리 내에 위치합니다. 이와 달리, 레거시인 `D3DCompiler_47.dll`는 NuGet에 의해 관리되지 않기에 `System32` 디렉토리에 위치합니다.  
      - `PodoRenderer\OutDir\dxcompiler.dll`

      - `C:\Windows\System32\D3DCompiler_47.dll`

<br>




### 4.3. 입력 처리
일반적인 윈도우 메시지 처리 방식을 사용하고 있습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 5. 측정 성능
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
- **렌더링 기초**
  - 외부 에셋 로드, 로딩 버튼 동기화
  - 정적 자원 관리(`DirectX::ResourceUploadBatch`), 동적 자원 관리(`DirectX::GraphicsMemory`), CPU-GPU 동기화(`Fence`)
  - 서술자 관리, 루트 서명, PSO
  - 정점, 인덱스, 조명, 텍스처매핑, 노말매핑 셰이더
  - SDR 감마 인코딩-디코딩
  - 카메라 조작 기능

<br>

- **렌더링 최적화**
  - 로딩 대상 선별      : 에셋 로딩 및 상주성 관리 정책
  - 로딩 대상 경량화    : 정적 LOD
  - 로딩 렌더 병렬화    : Copy Queue
  - 자원 관리 비용 검증 : `DirectX::ResourceUploadBatch`, `DirectX::GraphicsMemory` 비용 측정 후 필요시 개선
  - 그리기 대상 선별    : 오브젝트 테이블, 절두체 선별
  - 루트 인자 변경 축소 : 셰이더 자원 테이블 간접 인덱싱
  - 그리기 명령 수 축소 : 인스턴싱
  - CPU 스레드 병렬화   : 가상 부하, 멀티스레드

<br>

- **렌더링 패스 추가**
  - 조명 패스   : 블랜딩, 그림자 매핑, 반사 입방체 매핑, 굴절 입방체 매핑, SSAO, 광역 조명(미정), 레이 트레이싱 옵션
  - 조형 패스   : 자체 지면, 수면, 스킨드 애니메이션, 파티클

<br>

- **렌더링 패스 최적화**
  - 패스 구조 비교    : 포워드 vs 지연 렌더링(+다중 렌더 타겟), 단일 vs 다중 뷰포트, 단일 vs 다중 렌더 타겟 어레이, 정적 LOD vs 테셀레이션 LOD vs 메쉬셰이더 LOD 옵션
  - 이너 패스 최적화  : 각 패스 연산 부하 절약
  - 아웃 패스 최적화  : Placed Resource 공간 활용, PSO 변경 횟수, 루트 서명 간접성, 루트 서명 크기, 루트 인자 변경 횟수, 그리기 명령 횟수, 입력 정점 데이터 종류(cf.입력 슬롯) 절약, 루트 매개변수 정렬

<br>

- **제시 개선**
  - `SetMaximumFrameLatency`
  - 렌더 버퍼의 톤 매핑, 색역 매핑 셰이더
  - GUI 버퍼의 기준 밝기 조정 셰이더
  - 위 과정과 함께 둘을 합성하여 백버퍼에 저장하는 패스
  - 백버퍼, GUI 해상도와 독립적인 렌더 해상도를 조절 기능
  - `DXGI_FORMAT_R10G10B10A2_UNORM`, `DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020` 색역 매핑, PQ 전달 함수

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
  실행 중 디바이스가 사라지는 경우는 흔치 않으며, 이를 감지하고 우회하는 로직 또한 간단하지 않기에 구현하지 않았습니다.

<br>

- **자체 ImGui 힙 할당자**  
  최신 ImGui는 SRV를 1 개만 사용하지 않고 여러 개 사용하기에, 서술자 힙의 일부를 할양하고 또 해제받는 할당자를 응용프로그램 작성자가 직접 구현해주어야 합니다. 다만 ImGui가 사용하는 서술자 개수가 많지 않기에 정교한 할당자를 직접 구현할 필요는 없다고 판단하여 Dear ImGui의 내부 예제에 실린 간단한 할당자를 일부 수정하여 사용하고 있습니다.

<br>

- **DPI 설정값 반영**  
  사용자는 화면에 나타나는 논리적인 요소들의 배율을 뜻하는 DPI를 윈도우의 디스플레이 설정을 통해 지정할 수 있습니다. 유저가 DPI 설정 값을 바꾸거나 이미 다른 값이 설정된 디스플레이로 창이 이동하게 될 시 렌더링 엔진의 GUI 크기에 이를 반영하는 것이 좋을 수 있으나, GUI 크기를 명시적으로 설정할 수 있도록 하는 것이 더 좋으리라 생각하여 이를 제외하였습니다. 본 렌더링 엔진은 DPI 설정값에 의한 윈도우의 자동 스케일링이 일어나지않도록 DPI AWARENESS를 메니페스트에 명시하였습니다. 그리고 윈도우의 DPI 설정값을 반영하는 로직을 작성하지 않고, 대신 옵션에서 GUI의 물리적 픽셀 배율을 50%, 75%, 100%, 125%, 150% 중에서 선택할 수 있도록 하였습니다.

<br>

- **WM_INPUT 메세지 처리**  
  `WM_INPUT` 메세지를 이용하면 윈도우에서 추상화한 마우스 움직임이 아닌, 마우스의 Raw 인풋을 그대로 받을 수 있어 마우스 인풋 처리 과정에서 정보 손실을 줄이고 윈도우의 마우스 가속 설정에 영향을 받지 않도록 할 수 있습니다. 그러나 창 모드 상태에서 렌더링 엔진 속 커서의 이동 속도와 외부에서의 윈도우 커서의 속도가 일관성을 가질 수 있도록 함과 동시에 간단히 구현할 수 있도록, WM_INPUT을 처리하지 않고 `WM_MOUSEMOVE`와 같은 기초적인 메세지를 처리하도록 구현하였습니다.

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