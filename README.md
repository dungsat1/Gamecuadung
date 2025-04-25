Game Rắn săn mồi (Snake) là một trò chơi điện tử kinh điển, xuất hiện từ những năm 1970 và trở nên phổ biến trên điện thoại Nokia vào cuối thập niên 1990. Người chơi điều khiển một con rắn di chuyển để ăn mồi và tránh va vào tường hoặc chính thân mình. Mỗi lần ăn mồi, rắn sẽ dài ra, khiến trò chơi ngày càng thử thách hơn. Với lối chơi đơn giản nhưng gây nghiện, Rắn săn mồi là một biểu tượng gắn liền với tuổi thơ của nhiều thế hệ.
Lối chơi, logic của game:
 - Người chơi điều khiển một con rắn di chuyển trên một màn hình lưới.
 - Mục tiêu là ăn các "mồi" xuất hiện ngẫu nhiên trên màn hình.
 - Khi ăn mồi, con rắn sẽ dài ra một ô.
 - Người chơi sử dụng phím Enter để bắt đầu trò chơi, các phím mũi tên (lên, xuống, trái, phải) để điều khiển hướng di chuyển của rắn, khi kết thúc sử dụng phím R nếu muốn chơi lại.
 - Trò chơi kết thúc khi con rắn tự cắn vào thân mình hoặc đâm vào tường.
Đồ họa, âm thanh:
     Đồ họa: 
       - Sử dụng các thư viện đồ họa SDL2, SDL2_image.
       - Rắn được biểu thị bằng các hình ảnh như đầu, thân, đuôi, khúc rẽ gắn lại với nhau (mỗi hình ảnh đề có kích thước 40x40 pixel).
   ![head](https://github.com/user-attachments/assets/6498f3b8-25ee-4f13-ab32-70d5d3e4aa9c)

   ![corner](https://github.com/user-attachments/assets/f5e94637-a0a9-473e-b487-37860393add2)

   ![body](https://github.com/user-attachments/assets/c182ba24-f045-4f1b-a2d4-9ba8c981279c)

   ![tail](https://github.com/user-attachments/assets/4c1aff98-2a4e-4004-a3ef-e660e8c40718)

       - Mồi là hình ảnh quả táo (40x40 pixel).

    ![apple](https://github.com/user-attachments/assets/35d0862f-a43c-4d71-915c-1a0fc53adc4f)
       - Background là hình ảnh có kích thước 760x720 pixel (trong đó phần tường bên trái, bên phải và phía dưới có độ rộng là 40 pixel, phần tường phía trên có độ rộng là 
80 pixel).

   ![background](https://github.com/user-attachments/assets/7b3bf0da-fdfb-4277-bfcc-17b040a86d1f)

   Khi thua cuộc sẽ có thông báo hiện lên màn hình, điểm số của bạn và hướng dẫn nếu muốn chơi lại.

![gameover](https://github.com/user-attachments/assets/a71e73cf-8f73-435e-b6e0-21d36b6786af)
  
      - Màu sắc tương phản dễ nhìn.
    Âm thanh: 
      - Sử dụng thư viện âm thanh SDL2_mixer.
      - Các hiệu ứng âm thanh được sử dụng (khi ăn mồi, khi thua cuộc).
      Ngoài ra còn sử dụng thư viện SDL2_ttf để hiển thị điểm số trên mà hình sau khi ăn mồi (điểm số hiện phía góc trên bên trái màn hình).
Cấu trúc của project game:
- main.cpp:
  1. Khởi tạo các biến trò chơi.
  2. Khởi tạo rắn, khởi tạo mồi.
  3. Xử lí phím bấm trên bàn phím.
  4. Vẽ màn hình khi bắt đầu, khi chơi và khi kết thúc.
  5. Vẽ rắn khi di chuyển (đi thẳng, rẽ hướng).
- constants.h: file chứa các thông số của chương trình game như màu sắc, kích thước cửa sổ, hướng di chuyển, lưu trữ tọa độ (x, y) của mỗi phân đoạn của rắn trên lưới.
- sdl_utils.h, sdl_utils.cpp:
  1. Khởi tạo SDL video (SDL_Init(SDL_INIT_VIDEO)), SDL_mixer (âm thanh, Mix_OpenAudio), SDL_image (hình ảnh, IMG_Init), và SDL_ttf (font chữ, TTF_Init). 
  2. Kiểm tra lỗi sau mỗi bước khởi tạo. Nếu có lỗi, in ra thông báo lỗi và trả về false. 
  3. Tạo cửa sổ SDL (SDL_CreateWindow). 
  4. Tạo renderer SDL (SDL_CreateRenderer). 
  5. Load các font chữ bằng TTF_OpenFont. 
  6. Trả về true nếu khởi tạo thành công
- game_logic.h, game_logic.cpp: kiểm tra xem rắn có va chạm với tường hay với thân của mình hay không (trả về false nếu có, trả về true nếu không).
- Ngoài ra project còn có các file hình ảnh (đầu, thân, khúc rẽ, đuôi, quả táo, background), file âm thanh (khi ăn mồi, khi thua cuộc), font chữ.
Các chức năng đã cài được cho game: 
  - Điều khiển con rắn di chuyển bằng các phím mũi tên. 
  - Tạo mồi ngẫu nhiên trên màn hình không trùng với thân rắn. 
  - Tăng chiều dài con rắn khi ăn mồi. 
  - Kiểm tra va chạm với tường và thân rắn. 
  - Hiển thị điểm số. 
  - Hiển thị thông báo khi thua cuộc. 
  - Âm thanh khi ăn mồi, thua cuộc. 
Nguồn tham khảo:
  - Gemini: hình ảnh.
  - Github: âm thanh.













