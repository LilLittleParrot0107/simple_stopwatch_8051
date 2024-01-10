# Simple_stopwatch_8051

Chương trình nhắm đến hai chức năng thường có của một chiếc đồng hồ là đếm ngược và bấm giờ. Đây là một chương trình đơn giản viết bằng ngôn ngữ lập trình C cho vi điều khiển 8051. Chương trình sử dụng bàn phím 4x4 để người dùng nhập giá trị và điều khiển đèn 7 đoạn để điều khiển, ngoài ra cung cấp loa để phản hồi quá trình đếm.

## Thiết lập phân cứng

- Kết nối bàn phím 4x4 vào port 1 của vi điều khiển 8051
- Kết nối đèn 7 đoạn vào port 0 và port 2 của vi điều khiển
- Kết nối loa vào port 1 chân 5 (SPEAK_PORT).

## Cấu trúc code

### Hằng và định nghĩa chân

- **'DELAY_COUNT'**: Hằng số thời gian đợi trong hàm **'delay'**
- **'SPEAKER_PORT'**: Chân được kết nối đến loa
- Các định nghĩa chân cho bàn phím và led 7 đoạn

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
- Điều chỉnh giá trị đếm ngược dựa trên nút được nhấn (1, 2, 5, 6, 3).
- Bắt đầu đếm ngược khi nhấn nút 3.

## Sử dụng

1. Kết nối phần cứng như mô tả trong phần "Thiết Lập Phần Cứng".
2. Biên dịch và nạp chương trình vào vi điều khiển 8051.
3. Bật nguồn và tương tác với bàn phím để đặt giá trị đếm ngược.
4. Nhấn nút 3 để bắt đầu đếm ngược.
5. Quan sát giá trị đếm ngược trên đèn 7 đoạn và lắng nghe âm thanh phản hồi.

