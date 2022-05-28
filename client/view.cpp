#include "view.h"

view::view() {
    main_process.current_session = &current_session;

    connect(&registration_process, SIGNAL(show_login_window_again()),
            &login_process, SLOT(show_login_window()));

    connect(&login_process, SIGNAL(show_registration_window()),
            &registration_process, SLOT(show()));

    //коннекты из логина
    qRegisterMetaType<std::string>("std::string");
    connect(&current_session.processor,
            SIGNAL(run_successful_login(std::string)), &login_process,
            SLOT(successful_login(std::string)));
    connect(&current_session.processor, SIGNAL(run_wrong_password()),
            &login_process, SLOT(wrong_password()));
    connect(&current_session.processor, SIGNAL(run_no_user()), &login_process,
            SLOT(no_user()));
    connect(&current_session.processor, SIGNAL(run_error()), &login_process,
            SLOT(error()));

    //коннекты из мейн виндов

    qRegisterMetaType<std::vector<std::string>>("std::vector<std::string>");
    connect(&login_process, SIGNAL(show_main_window()), &main_process,
            SLOT(show_after_auth()));

    connect(&main_process, SIGNAL(turn_mic_on()),
            &current_session.audio_processor, SLOT(input_audio_on()));
    connect(&main_process, SIGNAL(turn_mic_off()),
            &current_session.audio_processor, SLOT(input_audio_off()));
    connect(&main_process, SIGNAL(turn_head_on()),
            &current_session.audio_processor, SLOT(output_audio_on()));
    connect(&main_process, SIGNAL(turn_head_off()),
            &current_session.audio_processor, SLOT(output_audio_off()));

    connect(&current_session.processor, SIGNAL(run_already_connected()),
            &main_process, SLOT(already_connected()));
    connect(&current_session.processor,
            SIGNAL(run_connect_with_room(std::vector<std::string>)),
            &main_process, SLOT(connect_with_room(std::vector<std::string>)));
    connect(&current_session.processor,
            SIGNAL(run_change_position(std::string, int, int)), &main_process,
            SLOT(user_changed_position(std::string, int, int)));
    connect(&current_session.processor,
            SIGNAL(run_disconnect_roommate(const std::string &)), &main_process,
            SLOT(roommate_disconnect(const std::string &)));
    connect(&current_session.processor,
            SIGNAL(run_connect_roommate(const std::string &)), &main_process,
            SLOT(roommate_connect(const std::string &)));

    connect(&login_process, SIGNAL(run_send_request(const std::string &)),
            &current_session, SLOT(send_request(const std::string &)));
    connect(&registration_process,
            SIGNAL(run_send_request(const std::string &)), &current_session,
            SLOT(send_request(const std::string &)));
    connect(&main_process, SIGNAL(run_send_request(const std::string &)),
            &current_session, SLOT(send_request(const std::string &)));

    connect(&current_session.processor, SIGNAL(run_successful_registration()),
            &registration_process, SLOT(successful_registration()));
    connect(&current_session.processor, SIGNAL(run_duplicate()),
            &registration_process, SLOT(duplicate()));

    connect(&login_process, SIGNAL(run_initialize(std::string, std::string)),
            &main_process.current_user,
            SLOT(initialize(std::string, std::string)));
}

void view::start() {
    login_process.show();
}
