# _Sample project_

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This is the simplest buildable example. The example is used by command `idf.py create-project`
that copies the project to user specified path and set it's name. For more information follow the [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project)

## How to use example
We encourage the users to use the example as a template for the new projects.
A recommended way is to follow the instructions on a [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project).

## Froject Module 
- camera.c <br>
    Khởi tạo camera ESP32. <br>
    Cấu hình và lấy ảnh từ camera. <br>
    Gửi ảnh đến hàm module face_recognition để nhận diện.

- sd_card.c <br>
    Khởi tạo thẻ SD. <br>
    Lưu sẵn các đặc trưng ảnh face sinh viên để nhận diện khuôn mặt. <br>
    Lưu database info thông tin sinh viên (JSON). <br>
    Tạo file điểm danh JSON để gửi lên server <br>
    Có thể là còn lưu mô hình nhận diện khuôn mặt.

- face_recognition.c <br>
So sánh khuôn mặt nhận diện với feature lưu sẵn cơ sở dữ liệu sinh viên. <br>
Trả về ID của sinh viên nếu nhận diện thành công, fail trả về -1 or mã lỗi.

- webserver.c <br>
Sử dụng HTTP POST REquest để gửi json điểm danh khi xong (có tín hiệu end). <br>
Gửi tín hiệu start/stop điểm danh từ web về ESP

- oled_display.c <br>
Hiển thị Check Done!, tên sinh viên, ID, time điểm danh lên màn hình OLED.

