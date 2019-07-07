-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jul 07, 2019 at 12:43 PM
-- Server version: 10.1.37-MariaDB
-- PHP Version: 5.6.40

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cocos_game`
--

-- --------------------------------------------------------

--
-- Table structure for table `player`
--

CREATE TABLE `player` (
  `id` int(11) NOT NULL COMMENT 'Số nguyên duy nhất đại diện cho mỗi tài khoản',
  `username` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Tên tài khoản, dùng để đăng nhập và dùng làm tên đại diện cho người chơi trong game',
  `password` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Mật khẩu, dùng để đăng nhập',
  `experience` int(11) NOT NULL DEFAULT '0' COMMENT 'Điểm kinh nghiệm trong game',
  `correct_answer` int(11) NOT NULL DEFAULT '0' COMMENT 'Tổng số câu trả lời đúng trong game',
  `wrong_answer` int(11) NOT NULL DEFAULT '0' COMMENT 'Tổng số câu trả lời sai trong game',
  `total_win` int(11) NOT NULL DEFAULT '0' COMMENT 'Tổng số lần chiến thắng trong game',
  `total_lose` int(11) NOT NULL DEFAULT '0' COMMENT 'Tổng số lần thất bại trong game',
  `total_kill` int(11) NOT NULL DEFAULT '0' COMMENT 'Tổng số quân địch hạ gục trong game',
  `friendship_point` int(11) NOT NULL DEFAULT '0' COMMENT 'Số điểm thân thiện hiện có trong game',
  `friendship_level` varchar(300) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'Frost Wyvern:0,Polar Bear:0,Enraged Ursa:0,Volcarona:0,Winged Orc:0,Poisonous Butterfly:0,Helicopter:0,Vampire Dragon:0,Liquid Assassin:0,Hotheaded Gunner:0,UFO Driver:0,Crazy Wolf:0,Dead Walker:0,Elemental Alien:0' COMMENT 'Cấp độ thân thiện của tất cả các loại quân trong game',
  `room_name` varchar(20) COLLATE utf8_unicode_ci NOT NULL DEFAULT '0' COMMENT 'Tên phòng của người chơi khi tạo phòng hay bắt cặp ngẫu nhiên',
  `ready` int(11) NOT NULL DEFAULT '0' COMMENT 'Thể hiện người chơi đã sẵn sàng tìm trận đấu',
  `submit_available` int(11) NOT NULL DEFAULT '0' COMMENT 'Số lượt tải lên câu hỏi đóng góp của người chơi',
  `status` int(11) NOT NULL DEFAULT '0' COMMENT 'Trạng thái, 0 là offline, 1 là online'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `player`
--

INSERT INTO `player` (`id`, `username`, `password`, `experience`, `correct_answer`, `wrong_answer`, `total_win`, `total_lose`, `total_kill`, `friendship_point`, `friendship_level`, `room_name`, `ready`, `submit_available`, `status`) VALUES
(1, 'Player001', 'Player001', 104, 6, 4, 5, 8, 10, 1, 'Frost Wyvern:1,Polar Bear:0,Enraged Ursa:0,Volcarona:0,Winged Orc:0,Poisonous Butterfly:0,Helicopter:2,Vampire Dragon:0,Liquid Assassin:0,Hotheaded Gunner:4,UFO Driver:0,Frozen Kingdom:0,Crazy Wolf:0,Dead Walker:0,Elemental Alien:0,Flamed Kingdom:0,Blessed Kingdom:0', '1', 0, 0, 0),
(2, 'ImaginysLight', 'ImaginysLight', 2, 1, 0, 1, 1, 8, 0, 'Frost Wyvern:0,Polar Bear:0,Enraged Ursa:0,Volcarona:0,Winged Orc:0,Poisonous Butterfly:0,Helicopter:0,Vampire Dragon:0,Liquid Assassin:0,Hotheaded Gunner:0,UFO Driver:0,Frozen Kingdom:0,Crazy Wolf:0,Dead Walker:0,Elemental Alien:0,Blessed Kingdom:0', '1', 0, 0, 0),
(3, 'LacLe', 'LacLe', 0, 0, 0, 0, 0, 0, 0, 'Frost Wyvern:0,Polar Bear:0,Enraged Ursa:0,Volcarona:0,Winged Orc:0,Poisonous Butterfly:0,Helicopter:0,Vampire Dragon:0,Liquid Assassin:0,Hotheaded Gunner:1,UFO Driver:0,Crazy Wolf:1,Dead Walker:0,Elemental Alien:0', '1', 0, 0, 0),
(4, 'Player003', 'Player003', 8, 4, 1, 0, 3, 2, 0, 'Frost Wyvern:0,Polar Bear:0,Enraged Ursa:0,Volcarona:0,Winged Orc:0,Poisonous Butterfly:0,Helicopter:0,Vampire Dragon:0,Liquid Assassin:0,Hotheaded Gunner:0,UFO Driver:0,Frozen Kingdom:0,Crazy Wolf:0,Dead Walker:0,Elemental Alien:0,Flamed Kingdom:0,Blessed Kingdom:0', '0', 0, 0, 1),
(5, 'Player004', 'Player004', 0, 0, 0, 0, 0, 0, 0, 'Frost Wyvern:0,Polar Bear:0,Enraged Ursa:0,Volcarona:0,Winged Orc:0,Poisonous Butterfly:0,Helicopter:0,Vampire Dragon:0,Liquid Assassin:0,Hotheaded Gunner:0,UFO Driver:0,Crazy Wolf:0,Dead Walker:0,Elemental Alien:0', '0', 0, 0, 0),
(6, 'meoconcute2k', 'meoconcute2k', 10000, 240, 120, 286, 100, 499, 25, 'Frost Wyvern:0,Polar Bear:0,Enraged Ursa:0,Volcarona:0,Winged Orc:0,Poisonous Butterfly:0,Helicopter:0,Vampire Dragon:0,Liquid Assassin:0,Hotheaded Gunner:0,UFO Driver:0,Crazy Wolf:0,Dead Walker:0,Elemental Alien:0', '0', 0, 0, 0),
(7, 'HackerAnonymousX.x.X', 'HackerAnonymousX.x.X', 6969, 1000, 1, 399, 1, 2000, 20, 'Frost Wyvern:0,Polar Bear:0,Enraged Ursa:0,Volcarona:0,Winged Orc:0,Poisonous Butterfly:0,Helicopter:0,Vampire Dragon:0,Liquid Assassin:0,Hotheaded Gunner:0,UFO Driver:0,Crazy Wolf:0,Dead Walker:0,Elemental Alien:0', '0', 0, 0, 0),
(8, 'Player002', 'Player002', 0, 0, 0, 0, 0, 0, 0, 'Frost Wyvern:0,Polar Bear:0,Enraged Ursa:0,Volcarona:0,Winged Orc:0,Poisonous Butterfly:0,Helicopter:0,Vampire Dragon:0,Liquid Assassin:0,Hotheaded Gunner:0,UFO Driver:0,Crazy Wolf:0,Dead Walker:0,Elemental Alien:0', '0', 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `question`
--

CREATE TABLE `question` (
  `id` int(11) NOT NULL COMMENT 'Số nguyên duy nhất đại diện cho mỗi câu hỏi',
  `content` text COLLATE utf8_unicode_ci NOT NULL COMMENT 'Nội dung của câu hỏi',
  `type` int(11) NOT NULL COMMENT 'Loại câu hỏi, 0 là câu lập trình, 1 là câu trắc nghiệm',
  `level` varchar(3) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Độ khó của câu hỏi',
  `answer` text COLLATE utf8_unicode_ci NOT NULL COMMENT 'Là kết quả của các test case nếu là câu hỏi lập trình, là 1 chữ cái đại diện cho đáp án đúng nếu là câu hỏi trắc nghiệm',
  `question_set_id` int(11) NOT NULL DEFAULT '0' COMMENT 'Khóa ngoại đến thuộc tính question_set(id), dùng để phân loại bộ câu hỏi',
  `status` int(11) NOT NULL COMMENT 'Trạng thái của câu hỏi, 0 là chưa được cho phép, 1 là đã được cho phép'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `question`
--

INSERT INTO `question` (`id`, `content`, `type`, `level`, `answer`, `question_set_id`, `status`) VALUES
(1, 'Để người dùng nhập giá trị cho biến ta dùng câu lệnh nào?', 1, '1', 'cin >> <tên biến>;', 0, 0),
(2, 'Để sử dụng các hàm nhập xuất cin, cout, ta cần thêm thư viện nào?', 1, '1', '#include<iostream>', 0, 0),
(3, 'Câu lệnh nào sau đây tạm dừng chương trình C++', 1, '1', 'system(\"pause\");', 0, 0),
(4, 'int a = 5 / 2 * 2 % 2;\r\nBiến a có giá trị bao nhiêu sau khi chạy lệnh trên?', 1, '2', '0', 0, 0),
(5, 'Viết hàm kiểm tra xem a và b có phải số nguyên tố hay không? Nếu đúng trả về 1, ngược lại trả về 0.', 0, '2', 'int PlayerFunction(int a, int b)', 0, 0),
(6, 'int result = a > b ? (a > c ? a : c) : (b > c ? b : c);\r\nCho 3 số nguyên a,b,c, biến result sẽ nhận được kết quả gì?', 1, '3', 'Số lớn nhất trong 3 số a,b,c', 0, 0),
(7, 'int i = 0;\r\nfor (; i < 10; i++){\r\n     int x = ++i + 1;\r\n     if (x>3) break;\r\n}\r\nSau vòng lặp trên giá trị của i là bao nhiêu?', 1, '3', '3', 0, 0),
(8, 'int i = 0;\r\nfor (; i < 10; i++){\r\n     int x = i++ + 1;\r\n     if (x>3) break;\r\n}\r\nSau vòng lặp trên giá trị của i là bao nhiêu?', 1, '3', '5', 0, 0),
(9, 'Viết hàm tính trung bình cộng 2 số nguyên a và b', 0, '1', 'int PlayerFuction(int a, int b)', 0, 0),
(10, 'Viết hàm tìm số lớn nhất trong 3 số nguyên a,b,c', 0, '1', 'int PlayerFunction(int a, int b, int c)', 0, 0),
(11, 'Kiểu dữ liệu nào sau đây không phù hợp?', 1, '2', 'long double int', 0, 0),
(12, 'int a = 0;\r\nswitch (a++){\r\n     case 0: ++a;\r\n     case 1: a++;\r\n     case 2: ++a;\r\n     default: a++; break;\r\n}\r\nBiến a có giá trị bao nhiêu sau đoạn lệnh trên?', 1, '2', '5', 0, 0),
(13, 'int a = 0;\r\nswitch (++a){\r\n     case 0: ++a;\r\n     case 1: a++;\r\n     case 2: ++a;\r\n     default: a++; break;\r\n}\r\nBiến a có giá trị bao nhiêu sau đoạn lệnh trên?', 1, '2', '4', 0, 0),
(14, 'Cho số nguyên a, viết hàm tìm SỐ LƯỢNG thừa số nguyên tố của a.', 0, '3', 'int PlayerFunction(int a)', 0, 0),
(15, 'int a = 1;\r\nint b = (++a << 2) % 4 == 0 ? a << 1 : a >> 1;\r\nBiến b có giá trị bao nhiêu sau đoạn code trên?', 1, '3', '4', 0, 0),
(16, 'Làm sao để ép kiểu số thực a sang số nguyên?', 1, '1', 'int result = (int) a;', 0, 0),
(17, 'int a = 0;\r\nif(5>6) a = 1;\r\nelse a = 2;\r\nelse if(9>6) a = 3;\r\nCho biết kết quả của đoạn lệnh trên.', 1, '1', 'Lỗi biên dịch', 0, 0),
(18, 'Viết hàm tìm số lớn nhì trong 4 số a,b,c,d', 0, '2', 'float PlayerFunction(int a, int b, int c, float d)', 0, 0),
(19, 'Cho số nguyên a (a>0). Tìm x và y sao cho x + y = x / y = a\r\nSố x có thể viết dưới dạng phân số tối giản. Viết hàm trả về số nguyên ghép lại từ phân số đó.\r\nVí dụ x=4/7 trả về 47, x=9/11 trả về 911.', 0, '3', 'int PlayerFunction(int a)', 0, 0),
(20, 'Cho số nguyên dương Viết hàm trả về a giai thừa.', 0, '2', 'int PlayerFunction(int a)', 0, 0),
(21, 'Viết hàm tính tổng các số lẻ trong mảng. Lưu ý có số âm.', 0, '2', 'int PlayerFunction(vector<int> arr)', 0, 0),
(22, 'Viết hàm tính tích các số nhỏ hơn hoặc bằng trung bình cộng của mảng.', 0, '2', 'int PlayerFunction(vector<int> arr)', 0, 0),
(23, 'Cho diện tích và chiều dài hình chữ nhật. Viết hàm tìm diện tích hình vuông tạo từ 3 cạnh của hình chữ nhật đó.', 0, '2', 'int PlayerFunction(int dientich, int chieudai)', 0, 0),
(24, 'Các lệnh dùng để lặp trong C++?', 1, '1', 'for, while, do...while', 0, 0),
(25, 'Jesse rất thích bánh ngọt. Cậu ta muốn tất cả bánh của mình phải có độ ngọt lớn hơn x. Jesse quyết định kết hợp bánh ít ngọt nhất (a) và ít ngọt nhì (b) tạo thành bánh mới có độ ngọt lầ a + 2*Và lặp đi lặp lại việc đó.\r\nCho một mảng chứa độ ngọt của bánh và số nguyên x. Viết hàm tìm số lượng bánh còn lại sau khi Jesse đã kết hợp để tất cả bánh đều có độ ngọt lớn hơn x.', 0, '4', 'int PlayerFunction(vector<int> sweet, int x)', 0, 0),
(26, 'Kiểu dữ liệu nào có kích thước lớn nhất?', 1, '1', 'double', 0, 0),
(27, 'Cách khai báo biến nào không hợp lệ?', 1, '1', 'long 2x;', 0, 0),
(28, 'Lệnh nào dùng để xuống dòng?', 1, '1', 'cout << endl;', 0, 0),
(29, 'int i = 5;\r\ncout << i++ - 2 << ++i << i++ << ++i;\r\nCho biết kết quả của đoạn lệnh sau', 1, '3', '6969', 0, 0),
(30, 'int a=1;\r\nfor( ;a<3; a++){\r\n     if(a==1) continue;\r\n     a--;\r\n     break;\r\n     a++;\r\n}\r\nGiá trị của a sau đoạn lệnh trên?', 1, '2', '1', 0, 0),
(31, 'Kết quả của biểu thức sqrt(4)+abs(12-16)-pow(2,3)', 1, '1', '-2', 0, 0),
(32, '#include<iostream>\r\nint a = 9.5 % 3;\r\nvoid main(){\r\n     if(a==1) cout << 3;\r\n     if(a==2) cout << 1;\r\n     if(a==3) cout << 2;\r\n}\r\nCho biết kết quả của đoạn code trên', 1, '1', 'Bị lỗi', 0, 0),
(33, 'Biểu thức nào sau đây sai?', 1, '3', '(3 * (2 + 1) >= 10 % 4 * 2 && \'a\' < \'A\') == 1', 0, 0),
(34, 'Cho biết kết quả của chương trình sau nếu lần lượt nhập vào 1, 5, 4, -3\r\nint a=0; d=0;\r\ndo{ cin >> a; d++ }\r\nwhile(a>0);\r\ncout << d;', 1, '2', '4', 0, 0),
(35, 'cin >> a >> b >> c;\r\nint x = a > b ? a : b;\r\nint n = c > x ? x : c;\r\nNhập vào lần lượt 4, 7, 5, cho biết kết quả của n sau đoạn code trên.', 1, '3', '5', 0, 0),
(36, 'Cho một mảng các số nguyên. Viết hàm tìm số trung vị biết số phần tử của mảng là số lẻ.', 0, '2', 'int PlayerFunction(vector<int> arr)', 0, 0),
(37, 'Cho 2 mảng a và Đếm số cặp phần tử chẵn trùng nhau và không phải số nguyên tố của 2 mảng.', 0, '2', 'int PlayerFunction(vector<int> a, vector<int> b)', 0, 0),
(38, 'Một biến được gọi là biến toàn cục nếu', 1, '1', 'Nó được khai báo ở ngoài tất cả các hàm kể cả hàm main.', 0, 0),
(39, 'int a = 2;\r\nint b = 10;\r\nauto x = a ^ b + a & b;\r\nKết quả của x sau đoạn code trên', 1, '3', '10', 0, 0),
(40, '5 > 7 | 8 < 9 || 6+9 == 69\r\nBiểu thức trên có giá trị bao nhiêu?', 1, '2', '1', 0, 0),
(41, 'int i = -1;\r\ndo{ for (; i;) i++; ++i; break; } while (!i);\r\nGiá trị của i sau đoạn code trên', 1, '2', '1', 0, 0),
(42, 'Bắt buộc phải có hàm main trong mỗi file .cpp. Nhận định này đúng hay sai?', 1, '1', 'Sai', 1, 0),
(43, 'Viết hàm tính tổng 2 số nguyên a và b', 0, '1', 'int Sum(int a, int b)', 2, 0);

-- --------------------------------------------------------

--
-- Table structure for table `question_choice`
--

CREATE TABLE `question_choice` (
  `id` int(11) NOT NULL,
  `content` varchar(500) COLLATE utf8_unicode_ci NOT NULL,
  `level` int(11) NOT NULL DEFAULT '1',
  `choice_1` varchar(100) COLLATE utf8_unicode_ci NOT NULL,
  `choice_2` varchar(100) COLLATE utf8_unicode_ci NOT NULL,
  `choice_3` varchar(100) COLLATE utf8_unicode_ci NOT NULL,
  `choice_4` varchar(100) COLLATE utf8_unicode_ci NOT NULL,
  `answer` varchar(100) COLLATE utf8_unicode_ci NOT NULL,
  `question_set_id` int(11) NOT NULL,
  `status` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `question_choice`
--

INSERT INTO `question_choice` (`id`, `content`, `level`, `choice_1`, `choice_2`, `choice_3`, `choice_4`, `answer`, `question_set_id`, `status`) VALUES
(1, 'Ai là người đẹp trai nhất vũ trụ', 1, 'Chương', 'Chương', 'Chương', 'Chương chứ ai nữa?', 'Chương chứ ai nữa?', 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `question_code`
--

CREATE TABLE `question_code` (
  `id` int(11) NOT NULL,
  `content` varchar(500) COLLATE utf8_unicode_ci NOT NULL,
  `level` int(11) NOT NULL,
  `prototype` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `test_case_1` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `answer_1` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `test_case_2` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `answer_2` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `test_case_3` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `answer_3` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `test_case_4` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `answer_4` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `question_set_id` int(11) NOT NULL,
  `status` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `question_code`
--

INSERT INTO `question_code` (`id`, `content`, `level`, `prototype`, `test_case_1`, `answer_1`, `test_case_2`, `answer_2`, `test_case_3`, `answer_3`, `test_case_4`, `answer_4`, `question_set_id`, `status`) VALUES
(1, 'Tính tổng 3 số nguyên.', 1, 'int Sum(int a, int b, int c)', 'Sum(1,2,3);', '6', 'Sum(1,2,4);', '7', 'Sum(1,2,5);', '8', 'Sum(1,-2,3);', '2', 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `question_set`
--

CREATE TABLE `question_set` (
  `id` int(11) NOT NULL COMMENT 'Số nguyên duy nhất đại diện cho mỗi bộ câu hỏi',
  `player_id` int(11) NOT NULL COMMENT 'Khóa ngoại tham chiếu đến thuộc tính player(id), chứa id của người tải lên bộ câu hỏi',
  `subject` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Chủ đề của bộ câu hỏi',
  `password` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Mật khẩu của bộ câu hỏi',
  `file_path` varchar(200) COLLATE utf8_unicode_ci NOT NULL DEFAULT '' COMMENT 'Đường dẫn đến tập tin bộ câu hỏi ở máy chủ',
  `upload_date` varchar(10) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Ngày tải lên',
  `status` int(11) NOT NULL DEFAULT '0' COMMENT 'Trạng thái của bộ câu hỏi, 0 là chưa được cho phép, 1 là đã được cho phép'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `question_set`
--

INSERT INTO `question_set` (`id`, `player_id`, `subject`, `password`, `file_path`, `upload_date`, `status`) VALUES
(1, 1, 'blablabla', '12345', 'Upload/1/558f2da546a51f5a7d14d9354411ca5a.txt', '30-03-2019', 1);

-- --------------------------------------------------------

--
-- Table structure for table `test_case`
--

CREATE TABLE `test_case` (
  `id` int(11) NOT NULL COMMENT 'Số nguyên duy nhất đại diện cho mỗi đáp án',
  `question` int(11) NOT NULL COMMENT 'Khóa ngoại tham chiếu đến thuộc tính question(id)',
  `content` text COLLATE utf8_unicode_ci NOT NULL COMMENT 'Nội dung của đáp án, là một lời gọi hàm nếu là câu hỏi lập trình, là một chuỗi đáp án nếu là câu hỏi trắc nghiệm',
  `result` text COLLATE utf8_unicode_ci NOT NULL COMMENT 'Kết quả của lời gọi hàm, chỉ dành cho câu hỏi lập trình'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `test_case`
--

INSERT INTO `test_case` (`id`, `question`, `content`, `result`) VALUES
(1, 1, 'cout >> <tên biến>;', ''),
(2, 1, 'cin >> <tên biến>;', ''),
(3, 1, 'cout << <tên biến>;', ''),
(4, 1, 'cin << <tên biến>;', ''),
(5, 2, '#include<stdio>', ''),
(6, 2, '#include<stdio.h>', ''),
(7, 2, '#include<iostream>', ''),
(8, 2, '#include<cin,cout>', ''),
(9, 3, 'system(\"pause\");', ''),
(10, 3, 'system(\"stop\");', ''),
(11, 3, 'std::pause();', ''),
(12, 3, 'std::delay();', ''),
(13, 4, '1', ''),
(14, 4, '4', ''),
(15, 4, '2', ''),
(16, 4, '0', ''),
(17, 5, 'PlayerFunction(2,3);', '1'),
(18, 5, 'PlayerFunction(17,37);', '1'),
(19, 5, 'PlayerFunction(83,102);', '0'),
(20, 5, 'PlayerFunction(0,5);', '0'),
(21, 6, 'Số nhỏ nhất trong 3 số a,b,c', ''),
(22, 6, 'Số lớn nhất trong 3 số a,b,c', ''),
(23, 6, 'Luôn là số a', ''),
(24, 6, 'Chả làm được gì cả', ''),
(25, 7, '2', ''),
(26, 7, '3', ''),
(27, 7, '4', ''),
(28, 7, '5', ''),
(29, 8, '5', ''),
(30, 8, '4', ''),
(31, 8, '3', ''),
(32, 8, '2', ''),
(33, 9, 'PlayerFunction(2,4);', '3'),
(34, 9, 'PlayerFunction(200,400);', '300'),
(35, 9, 'PlayerFunction(50,50);', '50'),
(36, 9, 'PlayerFunction(-100,-40);', '-70'),
(37, 10, 'PlayerFunction(1,2,3);', '3'),
(38, 10, 'PlayerFunction(1,-220,100);', '100'),
(39, 10, 'PlayerFunction(1,-2,-3);', '1'),
(40, 10, 'PlayerFunction(0,5,-8);', '5'),
(41, 11, 'unsigned int', ''),
(42, 11, 'long double', ''),
(43, 11, 'long long int', ''),
(44, 11, 'long double int', ''),
(45, 12, '3', ''),
(46, 12, '4', ''),
(47, 12, '5', ''),
(48, 12, '6', ''),
(49, 13, '3', ''),
(50, 13, '4', ''),
(51, 13, '5', ''),
(52, 13, '6', ''),
(53, 14, 'PlayerFunction(225);', '4'),
(54, 14, 'PlayerFunction(69);', '2'),
(55, 14, 'PlayerFunction(476);', '4'),
(56, 14, 'PlayerFunction(13);', '1'),
(57, 15, '1', ''),
(58, 15, '2', ''),
(59, 15, '3', ''),
(60, 15, '4', ''),
(61, 16, 'int result = a.floatToInt();', ''),
(62, 16, 'int result = (integer) a;', ''),
(63, 16, 'int result = ToInt(a);', ''),
(64, 16, 'int result = (int) a;', ''),
(65, 17, 'Lỗi biên dịch', ''),
(66, 17, 'a = 1', ''),
(67, 17, 'a = 2', ''),
(68, 17, 'a = 3', ''),
(69, 18, 'PlayerFunction(1,2,3,4);', '3'),
(70, 18, 'PlayerFunction(-1,65,89,4);', '65'),
(71, 18, 'PlayerFunction(1,2,3,2.5);', '2.5'),
(72, 18, 'PlayerFunction(3,6,9,6.9);', '6.9'),
(73, 19, 'PlayerFunction(10);', '1011'),
(74, 19, 'PlayerFunction(20);', '2021'),
(75, 19, 'PlayerFunction(69);', '6970'),
(76, 19, 'PlayerFunction(13);', '1314'),
(77, 20, 'PlayerFunction(5);', '120'),
(78, 20, 'PlayerFunction(10);', '3628800'),
(79, 20, 'PlayerFunction(3);', '6'),
(80, 20, 'PlayerFunction(8);', '40320'),
(81, 21, 'PlayerFunction(vector<int> {2,3,4,5,6});', '8'),
(82, 21, 'PlayerFunction(vector<int> {-21, 34, 45, -42, 6});', '24'),
(83, 21, 'PlayerFunction(vector<int> {-214, 343, 451, -432, 61});', '855'),
(84, 21, 'PlayerFunction(vector<int> {-14, 33, -51, 0, -1, 42, 626, 214, -323});', '342'),
(85, 22, 'PlayerFunction(vector<int> {-14, 33, -51, 0, -1, 42, 626, 214, -323});', '0'),
(86, 22, 'PlayerFunction(vector<int> {14, 333, 26, 214, 23});', '8372'),
(87, 22, 'PlayerFunction(vector<int> {1,1,1,1,1,1,1,1,2});', '1'),
(88, 22, 'PlayerFunction(vector<int> {-21,-41,221,-42,-11,12,142});', '4773384'),
(89, 23, 'PlayerFunction(20,5);', '16'),
(90, 23, 'PlayerFunction(200,100);', '4'),
(91, 23, 'PlayerFunction(21,7);', '9'),
(92, 23, 'PlayerFunction(925,37);', '625'),
(93, 24, 'if, while, if...else', ''),
(94, 24, 'for, while, switch...case, foreach', ''),
(95, 24, 'for, while, do...while', ''),
(96, 24, 'if...else, switch...case', ''),
(97, 25, 'PlayerFunction(vector<int> {2, 5, 8, 3, 7, 3}, 5);', '4'),
(98, 25, 'PlayerFunction(vector<int> {22, 13, 8, 1, 9, 15, 42}, 22);', '3'),
(99, 25, 'PlayerFunction(vector<int> {12, 13, 8, 1, 2}, 5);', '3'),
(100, 25, 'PlayerFunction(vector<int> {12, 13, 58, 12, 21, 30, 4, 22}, 17);', '6'),
(101, 26, 'int', ''),
(102, 26, 'char', ''),
(103, 26, 'long', ''),
(104, 26, 'double', ''),
(105, 27, 'int a;', ''),
(106, 27, 'char ky_tu;', ''),
(107, 27, 'long 2x;', ''),
(108, 27, 'double lac_le_lac_le;', ''),
(109, 28, 'cout << endl;', ''),
(110, 28, 'cout << \"/n\";', ''),
(111, 28, 'system(\"endline\");', ''),
(112, 28, 'Hey C++, down the line please;', ''),
(113, 29, '9999', ''),
(114, 29, '6969', ''),
(115, 29, '7999', ''),
(116, 29, '3656', ''),
(117, 30, '0', ''),
(118, 30, '1', ''),
(119, 30, '2', ''),
(120, 30, '3', ''),
(121, 31, '-2', ''),
(122, 31, '4', ''),
(123, 31, '21', ''),
(124, 31, '-10', ''),
(125, 32, '2', ''),
(126, 32, '1', ''),
(127, 32, 'Bị lỗi', ''),
(128, 32, '3', ''),
(129, 33, '((4 + 2 > 5) && (2 < 4 / 2)) == 0', ''),
(130, 33, '(1+1==2) == 1', ''),
(131, 33, '(3 * (2 + 1) >= 10 % 4 * 2 && \'a\' < \'A\') == 1', ''),
(132, 33, 'int a; a = 5 == 5 == 1', ''),
(133, 34, '6', ''),
(134, 34, '1', ''),
(135, 34, '4', ''),
(136, 34, '5', ''),
(137, 35, '5', ''),
(138, 35, '7', ''),
(139, 35, '4', ''),
(140, 35, 'Tất cả đều sai', ''),
(141, 36, 'PlayerFunction(vector<int> {1,1,1,1,1,1,100});', '1'),
(142, 36, 'PlayerFunction(vector<int> {2,32,22,12,5});', '12'),
(143, 36, 'PlayerFunction(vector<int> {4,69,69,69,69,15,36});', '69'),
(144, 36, 'PlayerFunction(vector<int> {502,205,205,11111,599,9954,123});', '502'),
(145, 37, 'PlayerFunction(vector<int {1,3,5,7}, vector<int> {2,3,4,5});', '0'),
(146, 37, 'PlayerFunction(vector<int {2,3,4,5,6}, vector<int> {6,5,2,2,2,1,2});', '2'),
(147, 37, 'PlayerFunction(vector<int {100,93,92,50}, vector<int> {5,4,8});', '0'),
(148, 37, 'PlayerFunction(vector<int {1,3,5,7,9,11,12}, vector<int> {2,4,6,8,10,12,14});', '1'),
(149, 38, 'Nó được khai báo ở ngoài tất cả các hàm ngoại trừ hàm main.', ''),
(150, 38, 'Nó được khai báo ở trong tất cả các hàm.', ''),
(151, 38, 'Nó được khai báo ở trong hàm main.', ''),
(152, 38, 'Nó được khai báo ở ngoài tất cả các hàm kể cả hàm main.', ''),
(153, 39, '\'1024 && 2&10\'', ''),
(154, 39, '10', ''),
(155, 39, '1036', ''),
(156, 39, 'Bị lỗi', ''),
(157, 40, '0', ''),
(158, 40, 'Bị lỗi', ''),
(159, 40, '1', ''),
(160, 40, '-1', ''),
(161, 41, '0', ''),
(162, 41, '1', ''),
(163, 41, '-1', ''),
(164, 41, 'Bị lỗi', ''),
(165, 42, 'Đúng', ''),
(166, 42, 'Sai', ''),
(167, 42, 'Không biết hàm main là gì', ''),
(168, 42, 'Vừa đúng vừa sai', ''),
(169, 43, 'Sum(1,2);', '3'),
(170, 43, 'Sum(-1,2);', '1'),
(171, 43, 'Sum(5,100);', '105'),
(172, 43, 'Sum(-100,100);', '0');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `player`
--
ALTER TABLE `player`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `question`
--
ALTER TABLE `question`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `question_choice`
--
ALTER TABLE `question_choice`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `question_code`
--
ALTER TABLE `question_code`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `question_set`
--
ALTER TABLE `question_set`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `test_case`
--
ALTER TABLE `test_case`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `player`
--
ALTER TABLE `player`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Số nguyên duy nhất đại diện cho mỗi tài khoản', AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `question`
--
ALTER TABLE `question`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Số nguyên duy nhất đại diện cho mỗi câu hỏi', AUTO_INCREMENT=44;

--
-- AUTO_INCREMENT for table `question_choice`
--
ALTER TABLE `question_choice`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `question_code`
--
ALTER TABLE `question_code`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `question_set`
--
ALTER TABLE `question_set`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Số nguyên duy nhất đại diện cho mỗi bộ câu hỏi', AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `test_case`
--
ALTER TABLE `test_case`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Số nguyên duy nhất đại diện cho mỗi đáp án', AUTO_INCREMENT=173;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
