#ifndef DATACONFIGURATION_H
#define DATACONFIGURATION_H
#include <QMap>
#include <QList>
#include <QVariant>

typedef unsigned char uchar;

/// EDR数据位置信息
/// {"Description",{a, b}}  a:Starting position, b:End position

const QMap<QString, QVector<int>> EDRDataPosition = {
    {"01Vertical deltaV", {0, 25}}
    ,{"02Max record length vertical deltaV", {26, 26}}
    ,{"03Reach max record length vertical deltaV time", {27, 27}}
    ,{"04Clipping flag", {28, 29}}
    ,{"05Vehicle speed", {30, 40}}
    ,{"06Service brake", {41, 51}}
    ,{"07Driver's seat belt status", {52, 52}}
    ,{"08Accelerator pedal position", {53, 63}}
    ,{"09Revolutions per minute", {64, 74}}
    ,{"10Power up period in the event", {75, 76}}
    ,{"11Power up period when reading", {77, 78}}
    ,{"12Event data record complete status", {79, 79}}
    ,{"13Time interval between this event and the last event", {80, 80}}
    ,{"14Vehicle Identification Number", {81, 97}}
    ,{"15ECU hardware number for recording EDR data", {98, 161}}
    ,{"16ECU serial number for recording EDR data", {162, 255}}
    ,{"17ECU software number for recording EDR data", {226, 289}}
    ,{"18Longitudinal acceleration", {290, 415}}
    ,{"19Lateral acceleration", {416, 541}}
    ,{"20Lateral deltaV", {542, 567}}
    ,{"21Maximum record lateral deltaV", {568, 568}}
    ,{"22Square of the maximum recorded horizontal deltaV", {569, 570}}
    ,{"23Time to reach the maximum recorded horizontal deltaV", {571, 571}}
    ,{"24Time to reach the maximum record total deltaV square", {572, 572}}
    ,{"25Yaw rate", {573, 594}}
    ,{"26Steering angle", {595, 616}}
    ,{"27Tend", {617, 617}}
    ,{"28Year", {618, 618}}
    ,{"29Month", {619, 619}}
    ,{"30Day", {620, 620}}
    ,{"31Hour", {621, 621}}
    ,{"32Minute", {622, 622}}
    ,{"33Second", {623, 623}}
    ,{"34Gear", {614, 634}}
    ,{"35Engine throttle position", {635, 645}}
    ,{"36Brake pedal position", {646, 656}}
    ,{"37Parking system status", {657, 667}}
    ,{"38Turn signal switch state", {668, 678}}
    ,{"39Driver's seat belt pre-tensioning device deployed state", {679, 680}}
    ,{"40Driver's frontal airbag deployment time(Phase1)", {681, 682}}
    ,{"41Driver's frontal airbag deployment time(Phase2)", {683, 684}}
    ,{"42Driver side airbag deployment time", {685, 686}}
    ,{"43Driver side air curtain deployment time", {687, 688}}
    ,{"44Front passenger seat belt status", {389, 689}}
    ,{"45Deployment time of front seat belt pre-tensioning device", {690, 691}}
    ,{"46Front passenger front airbag suppression status", {692, 692}}
    ,{"47Front passenger front airbag deployment time(Phase1)", {693, 694}}
    ,{"48Front passenger front airbag deployment time(Phase2)", {695, 696}}
    ,{"49Front passenger side airbag deployment time", {697, 698}}
    ,{"50Front passenger side air curtain deployment time", {699, 700}}
    ,{"51Occupant protection system status alarm", {701, 701}}
    ,{"52Tire pressure monitoring system status alarm", {702, 702}}
    ,{"53Braking system alarm status", {703, 703}}
    ,{"54Cruise control system status", {704,714}}
    ,{"55Adaptive cruise system", {715, 725}}
    ,{"56Anti-lock brake system status", {726, 736}}
    ,{"57Automatic emergency braking system status", {737, 747}}
    ,{"58Electronic stability control system status", {748, 758}}
    ,{"59Traction control system status", {759, 769}}
    ,{"60Synchronize the timing before the event", {770, 771}}
};

const QMap<QString, QVector<int>> EDRDataPositionCHN = {
    {"01纵向 delta-V", {0, 25}}
    ,{"02最大记录纵向 delta-V", {26, 26}}
    ,{"03达到最大记录纵向 delta-V 时间", {27, 27}}
    ,{"04削波标志", {28, 29}}
    ,{"05车辆速度", {30, 40}}
    ,{"06行车制动", {41, 51}}
    ,{"07驾驶员安全带状态", {52, 52}}
    ,{"08加速踏板位置", {53, 63}}
    ,{"09每分钟转数", {64, 74}}
    ,{"10事件中上电周期", {75, 76}}
    ,{"11读取时上电周期", {77, 78}}
    ,{"12事件数据记录完整状态", {79, 79}}
    ,{"13本次事件距上次事件的时间间隔", {80, 80}}
    ,{"14车辆识别代号", {81, 97}}
    ,{"15记录EDR数据的ECU硬件编号", {98, 161}}
    ,{"16记录EDR数据的ECU序列号", {162, 225}}
    ,{"17记录EDR数据的ECU软件编号", {226, 289}}
    ,{"18纵向加速度", {290, 415}}
    ,{"19横向加速度", {416, 541}}
    ,{"20横向 delta-V", {542, 567}}
    ,{"21最大记录横向 delta-V", {568, 568}}
    ,{"22最大记录合量 delta-V 平方", {569, 570}}
    ,{"23达到最大记录横向 delta-V 时间", {571, 571}}
    ,{"24达到最大记录合量 delta-V 平方的时间", {572, 572}}
    ,{"25横摆角速度", {573, 594}}
    ,{"26转向角度", {595, 616}}
    ,{"27Tend", {617, 617}}
    ,{"28年", {618, 618}}
    ,{"29月", {619, 619}}
    ,{"30日", {620, 620}}
    ,{"31时", {621, 621}}
    ,{"32分", {622, 622}}
    ,{"33秒", {623, 623}}
    ,{"34挡位", {624, 634}}
    ,{"35发动机节气门位置", {635, 645}}
    ,{"36制动踏板位置", {646, 656}}
    ,{"37驻车系统状态", {657, 667}}
    ,{"38转向信号开关状态", {668, 678}}
    ,{"39驾驶员安全带预紧装置展开时间", {679, 680}}
    ,{"40驾驶员正面气囊展开时间(第一阶段)", {681, 682}}
    ,{"41驾驶员正面气囊展开时间(第二阶段)", {683, 684}}
    ,{"42驾驶员侧面气囊展开时间", {685, 686}}
    ,{"43驾驶员侧气帘展开时间", {687, 688}}
    ,{"44前排乘员安全带状态", {689, 689}}
    ,{"45前排乘员安全带预紧器装置展开时间", {690, 691}}
    ,{"46前排乘员正面气囊抑制状态", {692, 692}}
    ,{"47前排乘员正面气囊展开时间(第一阶段)", {693, 694}}
    ,{"48前排乘员正面气囊展开时间(第二阶段)", {695, 696}}
    ,{"49前排乘员侧气囊展开时间", {697, 698}}
    ,{"50前排乘员侧气帘展开时间", {699, 700}}
    ,{"51乘员保护系统报警状态", {701, 701}}
    ,{"52轮胎压力监测系统报警状态", {702, 702}}
    ,{"53制动系统报警状态", {703, 703}}
    ,{"54定速巡航系统状态", {704, 714}}
    ,{"55自适应巡航系统状态", {715, 725}}
    ,{"56防抱制动系统状态", {726, 736}}
    ,{"57自动紧急制动系统状态", {737, 747}}
    ,{"58电子稳定性控制系统状态", {748, 758}}
    ,{"59牵引力控制系统状态", {759, 769}}
    ,{"60事件前同步计时时间", {770, 771}}
};

#if 0
struct EDRData {
    QVector<int> vertical_deltaV[26]{};  /// 纵向delta-V
    QVector<int> max_record_length_vertical_deltaV[1]{};  /// 最大记录纵向 delta-V
    QVector<int> reach_max_record_length_vertical_deltaV_time[1]{};  ///
    QVector<int> clipping_flag[1]{};  ///
    QVector<int> vehicle_speed[11]{};  ///
    QVector<char> service_brake[11]{};  ///
    QVector<char> driver_seat_belt_status[1]{};  /// 驾驶员安全带状态
    QVector<char> accelerator_pedal_position[11]{};   /// 加速踏板位置，全开位置百分比
    QVector<int>  revolutions_per_minute[11]{};   /// 每分钟转数
    QVector<uint> power_up_period_in_the_event[1]{};   /// 事件中上电周期
    QVector<uint> power_up_period_when_reading[1]{};   /// 读取时上电周期
    QVector<char> event_data_record_complete_status[1]{};  ///
    QVector<double> time_interval_between_this_event_and_the_last_event[1]{};
    QVector<char> vehicle_identification_number[17]{};  /// 车辆识别代号
    QVector<char> ECU_hardware_number_for_recording_EDR_data[64]{};  /// 记录EDR数据的ECU硬件版本号
    QVector<char> ECU_serial_number_for_recording_EDR_data[64]{};
    QVector<char> ECU_software_number_for_recording_EDR_data[64]{};
    QVector<int> longitudinal_acceleration[126]{};  /// 纵向加速度
    QVector<int> lateral_acceleration[126]{};  /// 横向加速度
    QVector<int> lateral_deltaV[26]{};  /// 横向delta-V
    QVector<int> maximum_record_lateral_deltaV[1]{};  /// 最大记录横向 delta-V
    QVector<int> square_of_the_maximum_recorded_horizontal_deltaV[1]{};  /// 最大记录合量 delta-V 平方
    QVector<double> time_to_reach_the_maximum_recorded_horizontal_deltaV[1]{};  /// 达到最大记录横向 delta-V 时间
    QVector<double> time_to_reach_the_maximum_record_total_deltaV_square[1]{};  /// 达到最大记录合量 delta-V 平方的时间
    QVector<double> yaw_rate[11]{};  /// 横摆角速度
    QVector<int> steering_angle[11]{};  /// 转向角度
    QVector<double> Tend[1]{};  /// Tend
    QVector<uint> year[1]{};  /// 年
    QVector<char> month[1]{};  /// 月
    QVector<char> day[1]{};  /// 日
    QVector<char> hour[1]{};  /// 时
    QVector<char> minute[1]{};  /// 分
    QVector<char> second[1]{};  /// 秒
    QVector<uchar> gear[11]{};  /// 挡位
    QVector<char> engine_throttle_position[11]{};  /// 发动机节气门位置，全开位置百分比
    QVector<uchar> brake_pedal_position[11]{};  /// 制动踏板位置
    QVector<char> parking_system_status[11]{};  /// 驻车系统状态
    QVector<char> turn_signal_switch_state[11]{};  /// 转向开关状态

};
#endif

struct EDRData {
    QMap<QString, QVector<QVariant>> EDR_data = {
        {"01Vertical deltaV", {}}
        ,{"02Max record length vertical deltaV", {}}
        ,{"03Reach max record length vertical deltaV time", {}}
        ,{"04Clipping flag", {}}
        ,{"05Vehicle speed", {}}
        ,{"06Service brake", {}}
        ,{"07Driver's seat belt status", {}}
        ,{"08Accelerator pedal position", {}}
        ,{"09Revolutions per minute", {}}
        ,{"10Power up period in the event", {}}
        ,{"11Power up period when reading", {}}
        ,{"12Event data record complete status", {}}
        ,{"13Time interval between this event and the last event", {}}
        ,{"14Vehicle Identification Number", {}}
        ,{"15ECU hardware number for recording EDR data", {}}
        ,{"16ECU serial number for recording EDR data", {}}
        ,{"17ECU software number for recording EDR data", {}}
        ,{"18Longitudinal acceleration", {}}
        ,{"19Lateral acceleration", {}}
        ,{"20Lateral deltaV", {}}
        ,{"21Maximum record lateral deltaV", {}}
        ,{"22Square of the maximum recorded horizontal deltaV", {}}
        ,{"23Time to reach the maximum recorded horizontal deltaV", {}}
        ,{"24Time to reach the maximum record total deltaV square", {}}
        ,{"25Yaw rate", {}}
        ,{"26Steering angle", {}}
        ,{"27Tend", {}}
        ,{"28Year", {}}
        ,{"29Month", {}}
        ,{"30Day", {}}
        ,{"31Hour", {}}
        ,{"32Minute", {}}
        ,{"33Second", {}}
        ,{"34Gear", {}}
        ,{"35Engine throttle position", {}}
        ,{"36Brake pedal position", {}}
        ,{"37Parking system status", {}}
        ,{"38Turn signal switch state", {}}
        ,{"39Driver's seat belt pre-tensioning device deployed state", {}}
        ,{"40Driver's frontal airbag deployment time(Phase1)", {}}
        ,{"41Driver's frontal airbag deployment time(Phase2)", {}}
        ,{"42Driver side airbag deployment time", {}}
        ,{"43Driver side air curtain deployment time", {}}
        ,{"44Front passenger seat belt status", {}}
        ,{"45Deployment time of front seat belt pre-tensioning device", {}}
        ,{"46Front passenger front airbag suppression status", {}}
        ,{"47Front passenger front airbag deployment time(Phase1)", {}}
        ,{"48Front passenger front airbag deployment time(Phase2)", {}}
        ,{"49Front passenger side airbag deployment time", {}}
        ,{"50Front passenger side air curtain deployment time", {}}
        ,{"51Occupant protection system status alarm", {}}
        ,{"52Tire pressure monitoring system status alarm", {}}
        ,{"53Braking system alarm status", {}}
        ,{"54Cruise control system status", {}}
        ,{"55Adaptive cruise system", {}}
        ,{"56Anti-lock brake system status", {}}
        ,{"57Automatic emergency braking system status", {}}
        ,{"58Electronic stability control system status", {}}
        ,{"59Traction control system status", {}}
        ,{"60Synchronize the timing before the event", {}}
    };

    QMap<QString, QVector<int>> EDR_data_CHN = {
        {"01纵向 delta-V", {}}
        ,{"02最大记录纵向 delta-V", {}}
        ,{"03达到最大记录纵向 delta-V 时间", {}}
        ,{"04削波标志", {}}
        ,{"05车辆速度", {}}
        ,{"06行车制动", {}}
        ,{"07驾驶员安全带状态", {}}
        ,{"08加速踏板位置", {}}
        ,{"09每分钟转数", {}}
        ,{"10事件中上电周期", {}}
        ,{"11读取时上电周期", {}}
        ,{"12事件数据记录完整状态", {}}
        ,{"13本次事件距上次事件的时间间隔", {}}
        ,{"14车辆识别代号", {}}
        ,{"15记录EDR数据的ECU硬件编号", {}}
        ,{"16记录EDR数据的ECU序列号", {}}
        ,{"17记录EDR数据的ECU软件编号", {}}
        ,{"18纵向加速度", {}}
        ,{"19横向加速度", {}}
        ,{"20横向 delta-V", {}}
        ,{"21最大记录横向 delta-V", {}}
        ,{"22最大记录合量 delta-V 平方", {}}
        ,{"23达到最大记录横向 delta-V 时间", {}}
        ,{"24达到最大记录合量 delta-V 平方的时间", {}}
        ,{"25横摆角速度", {}}
        ,{"26转向角度", {}}
        ,{"27Tend", {}}
        ,{"28年", {}}
        ,{"29月", {}}
        ,{"30日", {}}
        ,{"31时", {}}
        ,{"32分", {}}
        ,{"33秒", {}}
        ,{"34挡位", {}}
        ,{"35发动机节气门位置", {}}
        ,{"36制动踏板位置", {}}
        ,{"37驻车系统状态", {}}
        ,{"38转向信号开关状态", {}}
        ,{"39驾驶员安全带预紧装置展开时间", {}}
        ,{"40驾驶员正面气囊展开时间(第一阶段)", {}}
        ,{"41驾驶员正面气囊展开时间(第二阶段)", {}}
        ,{"42驾驶员侧面气囊展开时间", {}}
        ,{"43驾驶员侧气帘展开时间", {}}
        ,{"44前排乘员安全带状态", {}}
        ,{"45前排乘员安全带预紧器装置展开时间", {}}
        ,{"46前排乘员正面气囊抑制状态", {}}
        ,{"47前排乘员正面气囊展开时间(第一阶段)", {}}
        ,{"48前排乘员正面气囊展开时间(第二阶段)", {}}
        ,{"49前排乘员侧气囊展开时间", {}}
        ,{"50前排乘员侧气帘展开时间", {}}
        ,{"51乘员保护系统报警状态", {}}
        ,{"52轮胎压力监测系统报警状态", {}}
        ,{"53制动系统报警状态", {}}
        ,{"54定速巡航系统状态", {}}
        ,{"55自适应巡航系统状态", {}}
        ,{"56防抱制动系统状态", {}}
        ,{"57自动紧急制动系统状态", {}}
        ,{"58电子稳定性控制系统状态", {}}
        ,{"59牵引力控制系统状态", {}}
        ,{"60事件前同步计时时间", {}}
    };

    QMap<QString, QVector<QString>> EDR_data_CHN_str = {
        {"01纵向 delta-V", {}}
        ,{"02最大记录纵向 delta-V", {}}
        ,{"03达到最大记录纵向 delta-V 时间", {}}
        ,{"04削波标志", {}}
        ,{"05车辆速度", {}}
        ,{"06行车制动", {}}
        ,{"07驾驶员安全带状态", {}}
        ,{"08加速踏板位置", {}}
        ,{"09每分钟转数", {}}
        ,{"10事件中上电周期", {}}
        ,{"11读取时上电周期", {}}
        ,{"12事件数据记录完整状态", {}}
        ,{"13本次事件距上次事件的时间间隔", {}}
        ,{"14车辆识别代号", {}}
        ,{"15记录EDR数据的ECU硬件编号", {}}
        ,{"16记录EDR数据的ECU序列号", {}}
        ,{"17记录EDR数据的ECU软件编号", {}}
        ,{"18纵向加速度", {}}
        ,{"19横向加速度", {}}
        ,{"20横向 delta-V", {}}
        ,{"21最大记录横向 delta-V", {}}
        ,{"22最大记录合量 delta-V 平方", {}}
        ,{"23达到最大记录横向 delta-V 时间", {}}
        ,{"24达到最大记录合量 delta-V 平方的时间", {}}
        ,{"25横摆角速度", {}}
        ,{"26转向角度", {}}
        ,{"27Tend", {}}
        ,{"28年", {}}
        ,{"29月", {}}
        ,{"30日", {}}
        ,{"31时", {}}
        ,{"32分", {}}
        ,{"33秒", {}}
        ,{"34挡位", {}}
        ,{"35发动机节气门位置", {}}
        ,{"36制动踏板位置", {}}
        ,{"37驻车系统状态", {}}
        ,{"38转向信号开关状态", {}}
        ,{"39驾驶员安全带预紧装置展开时间", {}}
        ,{"40驾驶员正面气囊展开时间(第一阶段)", {}}
        ,{"41驾驶员正面气囊展开时间(第二阶段)", {}}
        ,{"42驾驶员侧面气囊展开时间", {}}
        ,{"43驾驶员侧气帘展开时间", {}}
        ,{"44前排乘员安全带状态", {}}
        ,{"45前排乘员安全带预紧器装置展开时间", {}}
        ,{"46前排乘员正面气囊抑制状态", {}}
        ,{"47前排乘员正面气囊展开时间(第一阶段)", {}}
        ,{"48前排乘员正面气囊展开时间(第二阶段)", {}}
        ,{"49前排乘员侧气囊展开时间", {}}
        ,{"50前排乘员侧气帘展开时间", {}}
        ,{"51乘员保护系统报警状态", {}}
        ,{"52轮胎压力监测系统报警状态", {}}
        ,{"53制动系统报警状态", {}}
        ,{"54定速巡航系统状态", {}}
        ,{"55自适应巡航系统状态", {}}
        ,{"56防抱制动系统状态", {}}
        ,{"57自动紧急制动系统状态", {}}
        ,{"58电子稳定性控制系统状态", {}}
        ,{"59牵引力控制系统状态", {}}
        ,{"60事件前同步计时时间", {}}
    };
};



#endif // DATACONFIGURATION_H
