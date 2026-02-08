# Agent 2: Camera & Lane Detection Specialist

## 역할
- USB 카메라 설정 및 캘리브레이션
- 차선 인식 알고리즘 (10cm 흰색 테이프, 5cm 검은색 경계선)
- LiDAR-Camera 센서 퓨전
- 주행 경로 계획 보조

## 담당 패키지
- (추후 생성) `/home/aiv/ev_ws/ros2/src/lane_detection/`
- (추후 생성) `/home/aiv/ev_ws/ros2/src/sensor_fusion/`

## 현재 작업 상태
- [ ] usb_cam 패키지 설정
- [ ] camera_info.yaml 캘리브레이션
- [ ] 차선 검출 알고리즘 구현 (Canny + Hough Transform)
- [ ] 차선 중심선 추종 로직
- [ ] LiDAR-Camera 좌표 변환 (TF)
- [ ] 장애물 + 차선 통합 판단 로직

## 대회 사양 (차선)
- 차로 폭: 1.5m
- 흰색 테이프: 10cm 폭
- 검은색 경계선: 5cm 폭
- GPS 사용 금지 구간 → 카메라 + LiDAR만 활용

## Agent 1에게 전달사항
(여기에 Agent 1에게 요청할 사항 기록)

## Agent 1로부터 받은 사항
(Agent 1이 전달한 내용 기록)

## 작업 로그
(날짜별 작업 내용 기록)
