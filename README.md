# Đồng Hồ Bấm Giờ và Đếm Ngược 8051

Chương trình này là một đồng hồ đơn giản được phát triển cho vi điều khiển 8051, cung cấp hai chức năng chính là bấm giờ và đếm ngược. Sử dụng ngôn ngữ lập trình C và tích hợp với bàn phím 4x4 và đèn 7 đoạn, chương trình mang lại trải nghiệm tương tác và hiển thị thời gian trên đèn LED.

## Thiết lập phân cứng

- Kết nối bàn phím 4x4 vào port 1 của vi điều khiển 8051
- Kết nối đèn 7 đoạn vào port 0 và port 2 của vi điều khiển
- Kết nối loa vào port 1 chân 5 (SPEAK_PORT).

## Cấu trúc code

### Hằng và định nghĩa chân

- **'DELAY_COUNT_DISPLAY'**: Thời gian chờ hiển thị trên đèn 7 đoạn.
- **'DELAY_COUNT_SPEED_UP'**: Thời gian chờ khi tăng tốc độ đếm ngược.
- **'DELAY_COUNT_SPEED_DOWN'**: Thời gian chờ khi giảm tốc độ đếm ngược.
- **'DELAY_COUNT_COUNTDOWN'**: Thời gian chờ trong quá trình đếm ngược.
- **'DELAY_COUNT_FINAL_DISPLAY'**: Thời gian chờ hiển thị cuối cùng sau khi đếm ngược kết thúc.
- **'SPEAKER_PORT'**: Chân được kết nối đến loa

## Khai báo hàm

- **'void delay(int time)'**: Hàm tạo đợi (delay)
- **'void init_keypad()'**: Khởi tạo phím trên port 1
- **'unsigned char read_keypad()'**: Đọc trạng thái của bàn phím và trả về nút được nhấn.
- **'int process_key(unsigned char key)'**: Ánh xạ nút nhấn thành một số cụ thể.
- **'void displaySeconds(int number, int delayCount)'**: Hiển thị giây lên đèn 7 đoạn.
- **'void countDown(int number)'**: Thực hiện chức năng đếm ngược với âm thanh từ loa.

## Hàm main

- Khởi tạo bàn phím.
- Vào vòng lặp vô hạn, liên tục kiểm tra đầu vào từ bàn phím.
- Điều chỉnh giá trị đếm ngược dựa trên nút được nhấn (1, 2, 5, 6).
- Điều chỉnh tốc độ giảm dựa trên nút được nhấn (3, 7)
- Bắt đầu đếm ngược khi nhấn nút 4.
- Tạm dừng quá trình giảm khi nhấn giữ nút 8

## Sử dụng

1. Kết nối phần cứng như mô tả trong phần "Thiết Lập Phần Cứng".
2. Biên dịch và nạp chương trình vào vi điều khiển 8051.
3. Bật nguồn và tương tác với bàn phím để đặt giá trị đếm ngược.
4. Nhấn nút 4 để bắt đầu đếm ngược.
5. Quan sát giá trị đếm ngược trên đèn 7 đoạn và lắng nghe âm thanh phản hồi. Nếu muốn tạm dừng quá trình đếm ngược, ấn giữ nút 8.
