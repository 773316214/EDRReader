/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version  : 1.0.2
** Author   : DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.08.21
**
****************************************************************************/
#ifndef DATACONFIGURATION_H
#define DATACONFIGURATION_H
#include <QMap>
#include <QList>
#include <QVariant>

typedef unsigned char UChar;

// EDR数据位置信息
// {"Description",{a, b}}  a:Starting position, b:End position

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
    QVector<int> vertical_deltaV[26]{};  // 纵向delta-V
    QVector<int> max_record_length_vertical_deltaV[1]{};  // 最大记录纵向 delta-V
    QVector<int> reach_max_record_length_vertical_deltaV_time[1]{};  //
    QVector<int> clipping_flag[1]{};  //
    QVector<int> vehicle_speed[11]{};  //
    QVector<char> service_brake[11]{};  //
    QVector<char> driver_seat_belt_status[1]{};  // 驾驶员安全带状态
    QVector<char> accelerator_pedal_position[11]{};   // 加速踏板位置，全开位置百分比
    QVector<int>  revolutions_per_minute[11]{};   // 每分钟转数
    QVector<uint> power_up_period_in_the_event[1]{};   // 事件中上电周期
    QVector<uint> power_up_period_when_reading[1]{};   // 读取时上电周期
    QVector<char> event_data_record_complete_status[1]{};  //
    QVector<double> time_interval_between_this_event_and_the_last_event[1]{};
    QVector<char> vehicle_identification_number[17]{};  // 车辆识别代号
    QVector<char> ECU_hardware_number_for_recording_EDR_data[64]{};  // 记录EDR数据的ECU硬件版本号
    QVector<char> ECU_serial_number_for_recording_EDR_data[64]{};
    QVector<char> ECU_software_number_for_recording_EDR_data[64]{};
    QVector<int> longitudinal_acceleration[126]{};  // 纵向加速度
    QVector<int> lateral_acceleration[126]{};  // 横向加速度
    QVector<int> lateral_deltaV[26]{};  // 横向delta-V
    QVector<int> maximum_record_lateral_deltaV[1]{};  // 最大记录横向 delta-V
    QVector<int> square_of_the_maximum_recorded_horizontal_deltaV[1]{};  // 最大记录合量 delta-V 平方
    QVector<double> time_to_reach_the_maximum_recorded_horizontal_deltaV[1]{};  // 达到最大记录横向 delta-V 时间
    QVector<double> time_to_reach_the_maximum_record_total_deltaV_square[1]{};  // 达到最大记录合量 delta-V 平方的时间
    QVector<double> yaw_rate[11]{};  // 横摆角速度
    QVector<int> steering_angle[11]{};  // 转向角度
    QVector<double> Tend[1]{};  // Tend
    QVector<uint> year[1]{};  // 年
    QVector<char> month[1]{};  // 月
    QVector<char> day[1]{};  // 日
    QVector<char> hour[1]{};  // 时
    QVector<char> minute[1]{};  // 分
    QVector<char> second[1]{};  // 秒
    QVector<uchar> gear[11]{};  // 挡位
    QVector<char> engine_throttle_position[11]{};  // 发动机节气门位置，全开位置百分比
    QVector<uchar> brake_pedal_position[11]{};  // 制动踏板位置
    QVector<char> parking_system_status[11]{};  // 驻车系统状态
    QVector<char> turn_signal_switch_state[11]{};  // 转向开关状态

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

struct AlgorithmIntermediateVarible {

  // 正碰ACU点火时刻需要记录的中间变量列表NV1x_V2
  const QMap<QString, QMap<QString, int>> front_crash_length {
    {"000_1LngAcc", {{"length", 400}, {"signed", true}}}
    ,{"000_2FrnPsnFrwAcc", {{"length", 400}, {"signed", true}}}
    ,{"000_3DrvFrwdAcc", {{"length", 400}, {"signed", true}}}
    ,{"001_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"002_PAS_OK_bits", {{"length", 1}, {"signed", false}}}
    ,{"003_AngleCrash_FrontLH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"004_AngleCrash_LR_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"005_AngleCrash_FrontRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"006_AngleCrash_RL_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"007_FrontPoleCrash_FrontLH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"008_FrontPoleCrash_LH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"009_FrontPoleCrash_FrontRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"010_FrontPoleCrash_RH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"011_SidePoleCrash_SILH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"012_SidePoleCrash_LH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"013_SidePoleCrash_SIRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"014_SidePoleCrash_RH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"015_Fcoff", {{"length", 4}, {"signed", true}}}
    ,{"016_SideLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"017_SideRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"018_AngleCrash_FLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"019_AngleCrash_FRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"020_FrontPoleCrash_FLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"021_FrontPoleCrash_FRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"022_SidePoleCrash_SLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"023_SidePoleCrash_SRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"024_AngleCrash_FISLR_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"025_AngleCrash_FISRL_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"026_FrontPoleCrash_FRLH_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"027_FrontPoleCrash_FRRH_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"028_SidePoleCrash_SILH_Disp_Y_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"029_SidePoleCrash_SIRH_Disp_Y_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"030_FrontCrash_AlgoCounter", {{"length", 1}, {"signed", false}}}
    ,{"031_FISLH_AlgoCounter", {{"length", 1}, {"signed", false}}}
    ,{"032_FISRH_AlgoCounter", {{"length", 1}, {"signed", false}}}
    ,{"033_FrontCrash_Threshold_Count", {{"length", 1}, {"signed", false}}}
    ,{"034_FISLH_Threshold_Count", {{"length", 1}, {"signed", false}}}
    ,{"035_FISRH_Threshold_Count", {{"length", 1}, {"signed", false}}}
    ,{"036_FrontCrash_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"037_FrontCrash_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"038_FrontCrash_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"039_FrontCrash_misc_bits2", {{"length", 1}, {"signed", false}}}
    ,{"040_FrontCrash_misc_bits3", {{"length", 1}, {"signed", false}}}
    ,{"041_FrontCrash_misc_bits4", {{"length", 1}, {"signed", false}}}
    ,{"042_FISLH_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"043_FISLH_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"044_FISLH_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"045_FISLH_misc_bits2", {{"length", 1}, {"signed", false}}}
    ,{"046_FISRH_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"047_FISRH_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"048_FISRH_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"049_FISRH_misc_bits2", {{"length", 1}, {"signed", false}}}
    ,{"050_Front_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"051_Front_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"052_bits_FISD_FireLevel1", {{"length", 1}, {"signed", false}}}
    ,{"053_bits_FISP_FireLevel1", {{"length", 1}, {"signed", false}}}
    ,{"054_RearCrash_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"055_FrontCrash_SavedAccltn_X_0", {{"length", 2}, {"signed", true}}}
    ,{"056_FrontCrash_SavedAccltn_X_1", {{"length", 2}, {"signed", true}}}
    ,{"057_FrontCrash_SavedAccltn_X_2", {{"length", 2}, {"signed", true}}}
    ,{"058_FrontCrash_SavedAccltn_X_3", {{"length", 2}, {"signed", true}}}
    ,{"059_FrontCrash_SavedAccltn_X_4", {{"length", 2}, {"signed", true}}}
    ,{"060_FrontCrash_SavedAccltn_X_5", {{"length", 2}, {"signed", true}}}
    ,{"061_FrontCrash_SavedAccltn_X_6", {{"length", 2}, {"signed", true}}}
    ,{"062_FrontCrash_SavedAccltn_X_7", {{"length", 2}, {"signed", true}}}
    ,{"063_FrontCrash_LowPassFilter_X", {{"length", 2}, {"signed", true}}}
    ,{"064_FrontCrash_Vel_X", {{"length", 4}, {"signed", false}}}
    ,{"065_FrontCrash_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"066_FrontCrash_Jrk", {{"length", 4}, {"signed", false}}}
    ,{"067_FrontCrash_PD_X", {{"length", 4}, {"signed", false}}}
    ,{"068_FrontCrash_DeltaVelocity", {{"length", 4}, {"signed", true}}}
    ,{"069_FrontCrash_DeltaVelocityCount", {{"length", 2}, {"signed", false}}}
    ,{"070_FrontCrash_LocalJrk", {{"length", 4}, {"signed", false}}}
    ,{"071_FrontCrash_Power", {{"length", 4}, {"signed", false}}}
    ,{"072_FrontCrash_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"073_FrontCrash_Jrkthreshold", {{"length", 2}, {"signed", false}}}
    ,{"074_FrontCrash_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"075_FrontCrash_DVthreshold", {{"length", 4}, {"signed", false}}}
    ,{"076_FrontCrash_LocalJrkthreshold", {{"length", 2}, {"signed", false}}}
    ,{"077_FrontCrash_Powerthreshold", {{"length", 4}, {"signed", false}}}
    ,{"078_FISLH_SavedAccltn_X_0", {{"length", 2}, {"signed", true}}}
    ,{"079_FISLH_SavedAccltn_X_1", {{"length", 2}, {"signed", true}}}
    ,{"080_FISLH_SavedAccltn_X_2", {{"length", 2}, {"signed", true}}}
    ,{"081_FISLH_SavedAccltn_X_3", {{"length", 2}, {"signed", true}}}
    ,{"082_FISLH_SavedAccltn_X_4", {{"length", 2}, {"signed", true}}}
    ,{"083_FISLH_SavedAccltn_X_5", {{"length", 2}, {"signed", true}}}
    ,{"084_FISLH_SavedAccltn_X_6", {{"length", 2}, {"signed", true}}}
    ,{"085_FISLH_SavedAccltn_X_7", {{"length", 2}, {"signed", true}}}
    ,{"086_FISLH_Vel_X", {{"length", 4}, {"signed", false}}}
    ,{"087_FISLH_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"088_FISLH_PD_X", {{"length", 4}, {"signed", false}}}
    ,{"089_FISLH_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"090_FISLH_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"091_FISRH_SavedAccltn_X_0", {{"length", 2}, {"signed", true}}}
    ,{"092_FISRH_SavedAccltn_X_1", {{"length", 2}, {"signed", true}}}
    ,{"093_FISRH_SavedAccltn_X_2", {{"length", 2}, {"signed", true}}}
    ,{"094_FISRH_SavedAccltn_X_3", {{"length", 2}, {"signed", true}}}
    ,{"095_FISRH_SavedAccltn_X_4", {{"length", 2}, {"signed", true}}}
    ,{"096_FISRH_SavedAccltn_X_5", {{"length", 2}, {"signed", true}}}
    ,{"097_FISRH_SavedAccltn_X_6", {{"length", 2}, {"signed", true}}}
    ,{"098_FISRH_SavedAccltn_X_7", {{"length", 2}, {"signed", true}}}
    ,{"099_FISRH_Vel_X", {{"length", 4}, {"signed", false}}}
    ,{"100_FISRH_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"101_FISRH_PD_X", {{"length", 4}, {"signed", false}}}
    ,{"102_FISRH_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"103_FISRH_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"104_RearCrash_LowPassFilter_X", {{"length", 2}, {"signed", true}}}
    ,{"105_RearCrash_Vel_X", {{"length", 4}, {"signed", false}}}
    ,{"106_RearCrash_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"107_RearCrash_PD_X", {{"length", 4}, {"signed", false}}}
    ,{"108_RearCrash_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"109_RearCrash_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"110_Reserve", {{"length", 1}, {"signed", false}}}
    ,{"111_Crash_Type", {{"length", 1}, {"signed", false}}}
    ,{"112_RearCrash_PD_X", {{"length", 1}, {"signed", false}}}
  };

  // 后碰ACU断电时刻需要记录的中间变量列表 NV1x_V2
  const QMap<QString, QMap<QString, int>> rear_crash_length {
    {"000_1LngAcc", {{"length", 400}, {"signed", true}}}
    ,{"000_2FrnPsnFrwAcc", {{"length", 400}, {"signed", true}}}
    ,{"000_3DrvFrwdAcc", {{"length", 400}, {"signed", true}}}
    ,{"001_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"002_PAS_OK_bits", {{"length", 1}, {"signed", false}}}
    ,{"003_AngleCrash_FrontLH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"004_AngleCrash_LR_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"005_AngleCrash_FrontRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"006_AngleCrash_RL_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"007_FrontPoleCrash_FrontLH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"008_FrontPoleCrash_LH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"009_FrontPoleCrash_FrontRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"010_FrontPoleCrash_RH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"011_SidePoleCrash_SILH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"012_SidePoleCrash_LH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"013_SidePoleCrash_SIRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"014_SidePoleCrash_RH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"015_Fcoff", {{"length", 4}, {"signed", true}}}
    ,{"016_SideLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"017_SideRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"018_AngleCrash_FLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"019_AngleCrash_FRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"020_FrontPoleCrash_FLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"021_FrontPoleCrash_FRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"022_SidePoleCrash_SLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"023_SidePoleCrash_SRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"024_AngleCrash_FISLR_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"025_AngleCrash_FISRL_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"026_FrontPoleCrash_FRLH_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"027_FrontPoleCrash_FRRH_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"028_SidePoleCrash_SILH_Disp_Y_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"029_SidePoleCrash_SIRH_Disp_Y_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"030_FrontCrash_AlgoCounter", {{"length", 1}, {"signed", false}}}
    ,{"031_FISLH_AlgoCounter", {{"length", 1}, {"signed", false}}}
    ,{"032_FISRH_AlgoCounter", {{"length", 1}, {"signed", false}}}
    ,{"033_FrontCrash_Threshold_Count", {{"length", 1}, {"signed", false}}}
    ,{"034_FISLH_Threshold_Count", {{"length", 1}, {"signed", false}}}
    ,{"035_FISRH_Threshold_Count", {{"length", 1}, {"signed", false}}}
    ,{"036_FrontCrash_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"037_FrontCrash_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"038_FrontCrash_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"039_FrontCrash_misc_bits2", {{"length", 1}, {"signed", false}}}
    ,{"040_FrontCrash_misc_bits3", {{"length", 1}, {"signed", false}}}
    ,{"041_FrontCrash_misc_bits4", {{"length", 1}, {"signed", false}}}
    ,{"042_FISLH_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"043_FISLH_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"044_FISLH_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"045_FISLH_misc_bits2", {{"length", 1}, {"signed", false}}}
    ,{"046_FISRH_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"047_FISRH_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"048_FISRH_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"049_FISRH_misc_bits2", {{"length", 1}, {"signed", false}}}
    ,{"050_Front_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"051_Front_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"052_bits_FISD_FireLevel1", {{"length", 1}, {"signed", false}}}
    ,{"053_bits_FISP_FireLevel1", {{"length", 1}, {"signed", false}}}
    ,{"054_RearCrash_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"055_FrontCrash_SavedAccltn_X_0", {{"length", 2}, {"signed", true}}}
    ,{"056_FrontCrash_SavedAccltn_X_1", {{"length", 2}, {"signed", true}}}
    ,{"057_FrontCrash_SavedAccltn_X_2", {{"length", 2}, {"signed", true}}}
    ,{"058_FrontCrash_SavedAccltn_X_3", {{"length", 2}, {"signed", true}}}
    ,{"059_FrontCrash_SavedAccltn_X_4", {{"length", 2}, {"signed", true}}}
    ,{"060_FrontCrash_SavedAccltn_X_5", {{"length", 2}, {"signed", true}}}
    ,{"061_FrontCrash_SavedAccltn_X_6", {{"length", 2}, {"signed", true}}}
    ,{"062_FrontCrash_SavedAccltn_X_7", {{"length", 2}, {"signed", true}}}
    ,{"063_FrontCrash_LowPassFilter_X", {{"length", 2}, {"signed", true}}}
    ,{"064_FrontCrash_Vel_X", {{"length", 4}, {"signed", false}}}
    ,{"065_FrontCrash_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"066_FrontCrash_Jrk", {{"length", 4}, {"signed", false}}}
    ,{"067_FrontCrash_PD_X", {{"length", 4}, {"signed", false}}}
    ,{"068_FrontCrash_DeltaVelocity", {{"length", 4}, {"signed", true}}}
    ,{"069_FrontCrash_DeltaVelocityCount", {{"length", 2}, {"signed", false}}}
    ,{"070_FrontCrash_LocalJrk", {{"length", 4}, {"signed", false}}}
    ,{"071_FrontCrash_Power", {{"length", 4}, {"signed", false}}}
    ,{"072_FrontCrash_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"073_FrontCrash_Jrkthreshold", {{"length", 2}, {"signed", false}}}
    ,{"074_FrontCrash_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"075_FrontCrash_DVthreshold", {{"length", 4}, {"signed", false}}}
    ,{"076_FrontCrash_LocalJrkthreshold", {{"length", 2}, {"signed", false}}}
    ,{"077_FrontCrash_Powerthreshold", {{"length", 4}, {"signed", false}}}
    ,{"078_FISLH_SavedAccltn_X_0", {{"length", 2}, {"signed", true}}}
    ,{"079_FISLH_SavedAccltn_X_1", {{"length", 2}, {"signed", true}}}
    ,{"080_FISLH_SavedAccltn_X_2", {{"length", 2}, {"signed", true}}}
    ,{"081_FISLH_SavedAccltn_X_3", {{"length", 2}, {"signed", true}}}
    ,{"082_FISLH_SavedAccltn_X_4", {{"length", 2}, {"signed", true}}}
    ,{"083_FISLH_SavedAccltn_X_5", {{"length", 2}, {"signed", true}}}
    ,{"084_FISLH_SavedAccltn_X_6", {{"length", 2}, {"signed", true}}}
    ,{"085_FISLH_SavedAccltn_X_7", {{"length", 2}, {"signed", true}}}
    ,{"086_FISLH_Vel_X", {{"length", 4}, {"signed", false}}}
    ,{"087_FISLH_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"088_FISLH_PD_X", {{"length", 4}, {"signed", false}}}
    ,{"089_FISLH_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"090_FISLH_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"091_FISRH_SavedAccltn_X_0", {{"length", 2}, {"signed", true}}}
    ,{"092_FISRH_SavedAccltn_X_1", {{"length", 2}, {"signed", true}}}
    ,{"093_FISRH_SavedAccltn_X_2", {{"length", 2}, {"signed", true}}}
    ,{"094_FISRH_SavedAccltn_X_3", {{"length", 2}, {"signed", true}}}
    ,{"095_FISRH_SavedAccltn_X_4", {{"length", 2}, {"signed", true}}}
    ,{"096_FISRH_SavedAccltn_X_5", {{"length", 2}, {"signed", true}}}
    ,{"097_FISRH_SavedAccltn_X_6", {{"length", 2}, {"signed", true}}}
    ,{"098_FISRH_SavedAccltn_X_7", {{"length", 2}, {"signed", true}}}
    ,{"099_FISRH_Vel_X", {{"length", 4}, {"signed", false}}}
    ,{"100_FISRH_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"101_FISRH_PD_X", {{"length", 4}, {"signed", false}}}
    ,{"102_FISRH_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"103_FISRH_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"104_RearCrash_LowPassFilter_X", {{"length", 2}, {"signed", true}}}
    ,{"105_RearCrash_Vel_X", {{"length", 4}, {"signed", false}}}
    ,{"106_RearCrash_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"107_RearCrash_PD_X", {{"length", 4}, {"signed", false}}}
    ,{"108_RearCrash_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"109_RearCrash_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"110_Reserve", {{"length", 1}, {"signed", false}}}
    ,{"111_Crash_Type", {{"length", 1}, {"signed", false}}}
    ,{"112_RearCrash_PD_X", {{"length", 1}, {"signed", false}}}
 };

  // 左侧ACU点火时刻需要记录的中间变量列表 NV1x_V2
  const QMap<QString, QMap<QString, int>> side_crash_lh_length {
    {"000_1LngAcc", {{"length", 400}, {"signed", true}}}
    ,{"000_2ExtAcc", {{"length", 400}, {"signed", true}}}
    ,{"001_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"002_PAS_OK_bits", {{"length", 1}, {"signed", false}}}
    ,{"003_AngleCrash_FrontLH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"004_AngleCrash_LR_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"005_AngleCrash_FrontRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"006_AngleCrash_RL_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"007_FrontPoleCrash_FrontLH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"008_FrontPoleCrash_LH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"009_FrontPoleCrash_FrontRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"010_FrontPoleCrash_RH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"011_SidePoleCrash_SILH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"012_SidePoleCrash_LH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"013_SidePoleCrash_SIRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"014_SidePoleCrash_RH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"015_Fcoff", {{"length", 4}, {"signed", true}}}
    ,{"016_SideLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"017_SideRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"018_AngleCrash_FLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"019_AngleCrash_FRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"020_FrontPoleCrash_FLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"021_FrontPoleCrash_FRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"022_SidePoleCrash_SLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"023_SidePoleCrash_SRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"024_SISLH_Threshold_Count", {{"length", 4}, {"signed", true}}}
    ,{"025_AngleCrash_FISRL_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"026_FrontPoleCrash_FRLH_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"027_FrontPoleCrash_FRRH_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"028_SidePoleCrash_SILH_Disp_Y_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"029_SidePoleCrash_SIRH_Disp_Y_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"030_SideCrashLH_AlgoCounter", {{"length", 1}, {"signed", false}}}
    ,{"031_SISLH_AlgoCounter", {{"length", 1}, {"signed", false}}}
    ,{"032_SideCrashLH_Threshold_Count", {{"length", 1}, {"signed", false}}}
    ,{"033_SISLH_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"034_SideCrashLH_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"035_SideCrashLH_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"036_SideCrashLH_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"037_SideCrashLH_misc_bits2", {{"length", 1}, {"signed", false}}}
    ,{"038_SideCrashLH_misc_bits3", {{"length", 1}, {"signed", false}}}
    ,{"039_SideCrashLH_misc_bits4", {{"length", 1}, {"signed", false}}}
    ,{"040_SISLH_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"041_SISLH_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"042_SISLH_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"043_SISLH_misc_bits2", {{"length", 1}, {"signed", false}}}
    ,{"044_SideLH_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"045_SideLH_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"046_bits_SISD_FireLevel1", {{"length", 1}, {"signed", false}}}
    ,{"047_SideCrashLH_SavedAccltn_Y_0", {{"length", 2}, {"signed", true}}}
    ,{"048_SideCrashLH_SavedAccltn_Y_1", {{"length", 2}, {"signed", true}}}
    ,{"049_SideCrashLH_SavedAccltn_Y_2", {{"length", 2}, {"signed", true}}}
    ,{"050_SideCrashLH_SavedAccltn_Y_3", {{"length", 2}, {"signed", true}}}
    ,{"051_SideCrashLH_SavedAccltn_Y_4", {{"length", 2}, {"signed", true}}}
    ,{"052_SideCrashLH_SavedAccltn_Y_5", {{"length", 2}, {"signed", true}}}
    ,{"053_SideCrashLH_SavedAccltn_Y_6", {{"length", 2}, {"signed", true}}}
    ,{"054_SideCrashLH_SavedAccltn_Y_7", {{"length", 2}, {"signed", true}}}
    ,{"055_SideCrashLH_LowPassFilter_Y", {{"length", 2}, {"signed", true}}}
    ,{"056_SideCrashLH_Vel_Y", {{"length", 4}, {"signed", false}}}
    ,{"057_SideCrashLH_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"058_SideCrashLH_Jrk", {{"length", 4}, {"signed", false}}}
    ,{"059_SideCrashLH_PD_Y", {{"length", 4}, {"signed", false}}}
    ,{"060_SideCrashLH_DeltaVelocity", {{"length", 4}, {"signed", true}}}
    ,{"061_SideCrashLH_DeltaVelocityCount", {{"length", 2}, {"signed", false}}}
    ,{"062_SideCrashLH_LocalJrk", {{"length", 4}, {"signed", false}}}
    ,{"063_SideCrashLH_Power", {{"length", 4}, {"signed", false}}}
    ,{"064_SideCrashLH_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"065_SideCrashLH_Jrkthreshold", {{"length", 2}, {"signed", false}}}
    ,{"066_SideCrashLH_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"067_SideCrashLH_DVthreshold", {{"length", 4}, {"signed", false}}}
    ,{"068_SideCrashLH_LocalJrkthreshold", {{"length", 2}, {"signed", false}}}
    ,{"069_SideCrashLH_Powerthreshold", {{"length", 4}, {"signed", false}}}
    ,{"070_SISLH_SavedAccltn_Y_0", {{"length", 2}, {"signed", true}}}
    ,{"071_SISLH_SavedAccltn_Y_1", {{"length", 2}, {"signed", true}}}
    ,{"072_SISLH_SavedAccltn_Y_2", {{"length", 2}, {"signed", true}}}
    ,{"073_SISLH_SavedAccltn_Y_3", {{"length", 2}, {"signed", true}}}
    ,{"074_SISLH_SavedAccltn_Y_4", {{"length", 2}, {"signed", true}}}
    ,{"075_SISLH_SavedAccltn_Y_5", {{"length", 2}, {"signed", true}}}
    ,{"076_SISLH_SavedAccltn_Y_6", {{"length", 2}, {"signed", true}}}
    ,{"077_SISLH_SavedAccltn_Y_7", {{"length", 2}, {"signed", true}}}
    ,{"078_SISLH_Vel_Y", {{"length", 4}, {"signed", false}}}
    ,{"079_SISLH_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"080_SISLH_PD_Y", {{"length", 4}, {"signed", false}}}
    ,{"081_SISLH_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"082_SISLH_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"083_Reserve", {{"length", 15}, {"signed", false}}}
    ,{"084_Crash_Type", {{"length", 1}, {"signed", false}}}
    ,{"085_Flag_Save_Completed", {{"length", 1}, {"signed", false}}}
  };

  // 右侧ACU点火时刻需要记录的中间变量列表 NV1x_V2
  const QMap<QString, QMap<QString, int>> side_crash_rh_length {
    {"000_1LngAcc", {{"length", 400}, {"signed", true}}}
    ,{"000_2ExtAcc", {{"length", 400}, {"signed", true}}}
    ,{"001_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"002_PAS_OK_bits", {{"length", 1}, {"signed", false}}}
    ,{"003_AngleCrash_FrontLH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"004_AngleCrash_LR_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"005_AngleCrash_FrontRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"006_AngleCrash_RL_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"007_FrontPoleCrash_FrontLH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"008_FrontPoleCrash_LH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"009_FrontPoleCrash_FrontRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"010_FrontPoleCrash_RH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"011_SidePoleCrash_SILH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"012_SidePoleCrash_LH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"013_SidePoleCrash_SIRH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"014_SidePoleCrash_RH_misc_bits1", {{"length", 1}, {"signed", false}}}
    ,{"015_Fcoff", {{"length", 4}, {"signed", true}}}
    ,{"016_SideLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"017_SideRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"018_AngleCrash_FLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"019_AngleCrash_FRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"020_FrontPoleCrash_FLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"021_FrontPoleCrash_FRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"022_SidePoleCrash_SLHcoff", {{"length", 4}, {"signed", true}}}
    ,{"023_SidePoleCrash_SRHcoff", {{"length", 4}, {"signed", true}}}
    ,{"024_AngleCrash_FISLR_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"025_AngleCrash_FISRL_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"026_FrontPoleCrash_FRLH_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"027_FrontPoleCrash_FRRH_Disp_X_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"028_SidePoleCrash_SILH_Disp_Y_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"029_SidePoleCrash_SIRH_Disp_Y_DiffValue", {{"length", 4}, {"signed", true}}}
    ,{"030_SideCrashRH_AlgoCounter", {{"length", 1}, {"signed", false}}}
    ,{"031_SISRH_AlgoCounter", {{"length", 1}, {"signed", false}}}
    ,{"032_SideCrashRH_Threshold_Count", {{"length", 1}, {"signed", false}}}
    ,{"033_SISRH_Threshold_Count", {{"length", 1}, {"signed", false}}}
    ,{"034_SideCrashRH_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"035_SideCrashRH_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"036_SideCrashRH_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"037_SideCrashRH_misc_bits2", {{"length", 1}, {"signed", false}}}
    ,{"038_SideCrashRH_misc_bits3", {{"length", 1}, {"signed", false}}}
    ,{"039_SideCrashRH_misc_bits4", {{"length", 1}, {"signed", false}}}
    ,{"040_SISRH_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"041_SISRH_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"042_SISRH_misc_bits", {{"length", 1}, {"signed", false}}}
    ,{"043_SISRH_misc_bits2", {{"length", 1}, {"signed", false}}}
    ,{"044_SideRH_fire_bits", {{"length", 1}, {"signed", false}}}
    ,{"045_SideRH_fire_bits2", {{"length", 1}, {"signed", false}}}
    ,{"046_bits_SISP_FireLevel1", {{"length", 1}, {"signed", false}}}
    ,{"047_SideCrashRH_SavedAccltn_Y_0", {{"length", 2}, {"signed", true}}}
    ,{"048_SideCrashRH_SavedAccltn_Y_1", {{"length", 2}, {"signed", true}}}
    ,{"049_SideCrashRH_SavedAccltn_Y_2", {{"length", 2}, {"signed", true}}}
    ,{"050_SideCrashRH_SavedAccltn_Y_3", {{"length", 2}, {"signed", true}}}
    ,{"051_SideCrashRH_SavedAccltn_Y_4", {{"length", 2}, {"signed", true}}}
    ,{"052_SideCrashRH_SavedAccltn_Y_5", {{"length", 2}, {"signed", true}}}
    ,{"053_SideCrashRH_SavedAccltn_Y_6", {{"length", 2}, {"signed", true}}}
    ,{"054_SideCrashRH_SavedAccltn_Y_7", {{"length", 2}, {"signed", true}}}
    ,{"055_SideCrashRH_LowPassFilter_Y", {{"length", 2}, {"signed", true}}}
    ,{"056_SideCrashRH_Vel_Y", {{"length", 4}, {"signed", false}}}
    ,{"057_SideCrashRH_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"058_SideCrashRH_Jrk", {{"length", 4}, {"signed", false}}}
    ,{"059_SideCrashRH_PD_Y", {{"length", 4}, {"signed", false}}}
    ,{"060_SideCrashRH_DeltaVelocity", {{"length", 4}, {"signed", true}}}
    ,{"061_SideCrashRH_DeltaVelocityCount", {{"length", 2}, {"signed", false}}}
    ,{"062_SideCrashRH_LocalJrk", {{"length", 4}, {"signed", false}}}
    ,{"063_SideCrashRH_Power", {{"length", 4}, {"signed", false}}}
    ,{"064_SideCrashRH_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"065_SideCrashRH_Jrkthreshold", {{"length", 2}, {"signed", false}}}
    ,{"066_SideCrashRH_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"067_SideCrashRH_DVthreshold", {{"length", 4}, {"signed", false}}}
    ,{"068_SideCrashRH_LocalJrkthreshold", {{"length", 2}, {"signed", false}}}
    ,{"069_SideCrashRH_Powerthreshold", {{"length", 4}, {"signed", false}}}
    ,{"070_SISRH_SavedAccltn_Y_0", {{"length", 2}, {"signed", true}}}
    ,{"071_SISRH_SavedAccltn_Y_1", {{"length", 2}, {"signed", true}}}
    ,{"072_SISRH_SavedAccltn_Y_2", {{"length", 2}, {"signed", true}}}
    ,{"073_SISRH_SavedAccltn_Y_3", {{"length", 2}, {"signed", true}}}
    ,{"074_SISRH_SavedAccltn_Y_4", {{"length", 2}, {"signed", true}}}
    ,{"075_SISRH_SavedAccltn_Y_5", {{"length", 2}, {"signed", true}}}
    ,{"076_SISRH_SavedAccltn_Y_6", {{"length", 2}, {"signed", true}}}
    ,{"077_SISRH_SavedAccltn_Y_7", {{"length", 2}, {"signed", true}}}
    ,{"078_SISRH_Vel_Y", {{"length", 4}, {"signed", false}}}
    ,{"079_SISRH_MD_Vel", {{"length", 4}, {"signed", false}}}
    ,{"080_SISRH_PD_Y", {{"length", 4}, {"signed", false}}}
    ,{"081_SISRH_Velthreshold", {{"length", 2}, {"signed", false}}}
    ,{"082_SISRH_PDthreshold", {{"length", 4}, {"signed", false}}}
    ,{"083_Reserve", {{"length", 15}, {"signed", false}}}
    ,{"084_Crash_Type", {{"length", 1}, {"signed", false}}}
    ,{"085_Flag_Save_Completed", {{"length", 1}, {"signed", false}}}
  };


};

#endif // DATACONFIGURATION_H
