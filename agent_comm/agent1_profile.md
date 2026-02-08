# Agent 1: LiDAR Processing Specialist

## 역할
- Patchwork++ 지면 분리 구현 및 파라미터 튜닝
- DBSCAN 클러스터링으로 장애물 탐지
- LiDAR 기반 장애물 회피 로직
- 포인트클라우드 전처리 (노이즈 제거, ROI 필터링)

## 담당 패키지
- `/home/aiv/ev_ws/ros2/src/patchwork-plusplus/`
- `/home/aiv/ev_ws/ros2/src/velodyne/`
- (추후 생성) `/home/aiv/ev_ws/ros2/src/obstacle_detection/`

## 현재 작업 상태
- [x] Patchwork++ 설치 완료
- [x] VLP-16 드라이버 설정 완료
- [x] LiDAR 전처리 파이프라인 설계 완료
- [x] ROI Filtering 구현 완료 (Patchwork++ 통합)
- [ ] **[진행 중]** Clustering (Euclidean/DBSCAN) 구현 ← 다음 단계
- [ ] 장애물 바운딩 박스 생성
- [ ] RViz2 시각화 (ground/non-ground/obstacles)
- [ ] Ground segmentation 파라미터 튜닝 (나중에)

## 핵심 파라미터
- VLP-16 IP: 192.168.1.201
- ROI Config: `ros2/src/patchwork-plusplus/ros/params/patchworkpp_params.yaml`
- min_range: 0.3m (최소 탐지 거리)
- Fixed Frame: "velodyne"
- ROSbag 데이터: `/home/aiv/ev_ws/ros2/rosbag/`

## Agent 2에게 전달사항
(여기에 Agent 2에게 요청할 사항 기록)

## Agent 2로부터 받은 사항
(Agent 2가 전달한 내용 기록)

## 작업 로그

### 2026-02-08
**ROI Filtering 구현 및 Config 파일 분리**

**주요 내용**:
- Patchwork++ 노드(`GroundSegmentationServer.cpp`) 내부에 ROI 필터링 로직 직접 구현.
- 하드코딩된 파라미터를 제거하고 `patchworkpp_params.yaml` 파일로 분리.
- Launch 파일이 YAML 설정 파일을 로드하도록 수정.

**코드 변경**:
- `ros2/src/patchwork-plusplus/ros/params/patchworkpp_params.yaml`: ROI 및 알고리즘 파라미터 정의
- `ros2/src/patchwork-plusplus/ros/src/GroundSegmentationServer.cpp`: ROI 파라미터 로딩 및 `ApplyROI` 함수 구현
- `ros2/src/patchwork-plusplus/ros/launch/patchworkpp.launch.py`: YAML 파일 로드 로직 추가

**다음 단계**: 
1. ROI가 적용된 PointCloud(`nonground`)를 사용하여 Clustering 구현
2. `GroundSegmentationServer.cpp`에 `Clustering` 함수 추가 예정
