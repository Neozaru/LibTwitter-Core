#ifndef _H_TEST_REQUESTS_H_
	#define _H_TEST_REQUESTS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextTestResult.h>

#include <cppunit/extensions/HelperMacros.h>

#include <Twitter/Core/TwitterSession.h>
#include <Twitter/Core/TwitterRequest.h>

#include <string>
#include <ostream>


const sch_id_t DEF_SCH_ID_T = "libtwitt3r_search";

const usr_id_t DEF_USR_NAME_T = "libtwitt3r_test"; // Name of a friend/user
const str_t DEF_STR_T = "This is the test default text "+std::string("#")+DEF_SCH_ID_T;
const slug_t DEF_SLUG_T = "libtwitt3r_slug";

/* Default IDs */
const usr_id_t DEF_USR_ID_T = "866264096";
const twt_id_t DEF_TWT_ID_T = "254929166833704960";
const msg_id_t DEF_MSG_ID_T = "37902443013496153052420350";

const lst_id_t DEF_LST_ID_T = "78612198";
const cur_id_t DEF_CUR_ID_T = "-1";


const bool DEF_BOOL = true;
const int DEF_INT = 20;
const float DEF_FLOAT = 57.123456;


static std::string g_user;
static std::string g_pass;

static std::string g_user_key;
static std::string g_user_secret;

static std::string g_log_file;


class Test_Requests  : public CppUnit::TestFixture {


    public:
        
    Test_Requests() : CppUnit::TestFixture() {


    }   


    ~Test_Requests() {}

        //~ Call before tests
        void setUp() {

            _session = new TwitterSession();
            //_session->set_debug_mode(DEBUG);

            /* *** */
            /* Set consummer keys and secrets. */
            /* It corresponds to your own app key/secret */
            /* *** */

            _session->get_oauth().set_consumer_key( "4wdGht7GCUYqMbLLsY8Yg" );
            _session->get_oauth().set_consumer_secret( "DmPp6hteK6bgR4JiKLbOqSFPNT0r35QFAlbRGjR3E" );

            /*************************************/

            if ( g_user_key.empty() || g_user_secret.empty() ) {
            
                const string& url = _session->generate_auth_URL();


                if ( _session->bypass_PIN_with_password( url, g_user, g_pass ) ) {
                    
                    std::cout << "Connected" << std::endl;

                    g_user_key = _session->get_oauth().get_token_key();
                    g_user_secret = _session->get_oauth().get_token_secret();

                }
                else {
                    std::cout << "Connection failed" << std::endl;
                    exit(0);
                }

            }
            else {

                std::cout << "Using user keys " << std::endl;

                _session->get_oauth().set_token_key( g_user_key );
                _session->get_oauth().set_token_secret( g_user_secret );

            }


        }

        //~ Call after tests
        void tearDown() {
            delete _session;
        }


    public:

        void test_request( TwitterRequest* req ) {

            req->send();

            std::stringstream stream;
            req->to_stream(stream);

            CPPUNIT_ASSERT_MESSAGE( 
                stream.str(), 
                req->get_response_code() == 200 
            );

        }

/* BEGIN_PYGEN don't remove this comment (2012/10/27 14:35) */
CPPUNIT_TEST_SUITE( Test_Requests );
CPPUNIT_TEST( mentions_timeline_test );
CPPUNIT_TEST( user_timeline_by_id_test );
CPPUNIT_TEST( user_timeline_test );
CPPUNIT_TEST( home_timeline_test );
CPPUNIT_TEST( get_retweets_test );
CPPUNIT_TEST( show_status_test );
CPPUNIT_TEST( destroy_status_test );
CPPUNIT_TEST( update_status_test );
CPPUNIT_TEST( retweet_test );
CPPUNIT_TEST( oembed_status_test );
CPPUNIT_TEST( search_tweets_test );
CPPUNIT_TEST( sent_direct_messages_test );
CPPUNIT_TEST( show_direct_messages_test );
CPPUNIT_TEST( destroy_direct_messages_test );
CPPUNIT_TEST( new_direct_message_by_id_test );
CPPUNIT_TEST( new_direct_message_test );
CPPUNIT_TEST( friends_ids_by_id_test );
CPPUNIT_TEST( friends_ids_test );
CPPUNIT_TEST( followers_ids_by_id_test );
CPPUNIT_TEST( followers_ids_test );
CPPUNIT_TEST( lookup_friendship_test );
CPPUNIT_TEST( lookup_friendship_by_ids_test );
CPPUNIT_TEST( incoming_friendships_test );
CPPUNIT_TEST( outgoing_friendships_test );
CPPUNIT_TEST( create_friendship_test );
CPPUNIT_TEST( create_friendship_by_id_test );
CPPUNIT_TEST( destroy_friendship_test );
CPPUNIT_TEST( destroy_friendship_by_id_test );
CPPUNIT_TEST( update_friendship_test );
CPPUNIT_TEST( update_friendship_by_id_test );
CPPUNIT_TEST( show_friendship_test );
CPPUNIT_TEST( show_friendship_by_id_test );
CPPUNIT_TEST( verify_credentials_test );
CPPUNIT_TEST( set_account_settings_test );
CPPUNIT_TEST( update_delivery_device_test );
CPPUNIT_TEST( update_profile_test );
CPPUNIT_TEST( update_profile_background_image_test );
CPPUNIT_TEST( update_profile_colors_test );
CPPUNIT_TEST( get_blocks_list_test );
CPPUNIT_TEST( get_blocks_ids_test );
CPPUNIT_TEST( create_blocks_test );
CPPUNIT_TEST( create_blocks_by_id_test );
CPPUNIT_TEST( destroy_blocks_test );
CPPUNIT_TEST( destroy_blocks_by_id_test );
CPPUNIT_TEST( lookup_user_by_id_test );
CPPUNIT_TEST( lookup_user_by_screen_name_test );
CPPUNIT_TEST( show_user_by_id_test );
CPPUNIT_TEST( show_user_test );
CPPUNIT_TEST( search_user_test );
CPPUNIT_TEST( user_contributees_by_user_id_test );
CPPUNIT_TEST( user_contributees_by_screen_name_test );
CPPUNIT_TEST( user_contributors_by_user_id_test );
CPPUNIT_TEST( user_contributors_by_screen_name_test );
CPPUNIT_TEST( user_suggestions_test );
CPPUNIT_TEST( user_suggestions_alt_test );
CPPUNIT_TEST( user_suggestions_members_test );
CPPUNIT_TEST( list_favorites_test );
CPPUNIT_TEST( list_favorites_by_screen_name_test );
CPPUNIT_TEST( destroy_favorite_test );
CPPUNIT_TEST( create_favorite_test );
CPPUNIT_TEST( lists_by_user_id_test );
CPPUNIT_TEST( lists_test );
CPPUNIT_TEST( list_statuses_by_ids_test );
CPPUNIT_TEST( list_statuses_test );
CPPUNIT_TEST( destroy_list_member_by_ids_test );
CPPUNIT_TEST( destroy_list_member_test );
CPPUNIT_TEST( list_membership_test );
CPPUNIT_TEST( list_membership_by_id_test );
CPPUNIT_TEST( list_suscribers_test );
CPPUNIT_TEST( list_suscribers_by_id_test );
CPPUNIT_TEST( subscribe_to_list_test );
CPPUNIT_TEST( subscribe_to_list_1_test );
CPPUNIT_TEST( show_user_is_suscriber_by_ids_test );
CPPUNIT_TEST( show_user_is_suscriber_test );
CPPUNIT_TEST( unsubscribe_from_list_test );
CPPUNIT_TEST( unsubscribe_from_list_1_test );
CPPUNIT_TEST( subscribe_to_list_multi_by_ids_test );
CPPUNIT_TEST( subscribe_to_list_multi_test );
CPPUNIT_TEST( show_user_is_member_by_ids_test );
CPPUNIT_TEST( show_user_is_member_test );
CPPUNIT_TEST( list_members_by_id_test );
CPPUNIT_TEST( list_members_test );
CPPUNIT_TEST( join_list_test );
CPPUNIT_TEST( join_list_1_test );
CPPUNIT_TEST( part_from_list_test );
CPPUNIT_TEST( update_list_by_id_test );
CPPUNIT_TEST( update_list_test );
CPPUNIT_TEST( create_list_test );
CPPUNIT_TEST( show_list_test );
CPPUNIT_TEST( show_list_1_test );
CPPUNIT_TEST( lists_subscription_by_id_test );
CPPUNIT_TEST( lists_subscription_test );
CPPUNIT_TEST( expulse_from_list_by_ids_test );
CPPUNIT_TEST( expulse_from_list_test );
CPPUNIT_TEST( get_saved_searches_test );
CPPUNIT_TEST( show_saved_search_test );
CPPUNIT_TEST( search_test );
CPPUNIT_TEST( destroy_saved_search_test );
CPPUNIT_TEST( trends_place_test );
CPPUNIT_TEST( available_trends_test );
CPPUNIT_TEST( closest_trend_test );
CPPUNIT_TEST( report_spam_test );
CPPUNIT_TEST( rate_limit_status_test );
CPPUNIT_TEST( help_languages_test );
CPPUNIT_TEST( help_privacy_test );
CPPUNIT_TEST( help_TOS_test );
CPPUNIT_TEST( application_rate_limit_status_test );CPPUNIT_TEST_SUITE_END();

public:
void mentions_timeline_test() {
	test_request( _session->mentions_timeline_request() );
}

void user_timeline_by_id_test() {
	test_request( _session->user_timeline_by_id_request(DEF_USR_ID_T) );
}

void user_timeline_test() {
	test_request( _session->user_timeline_request(DEF_USR_NAME_T) );
}

void home_timeline_test() {
	test_request( _session->home_timeline_request() );
}

void get_retweets_test() {
	test_request( _session->get_retweets_request(DEF_TWT_ID_T) );
}

void show_status_test() {
	test_request( _session->show_status_request(DEF_TWT_ID_T) );
}

void destroy_status_test() {
	test_request( _session->destroy_status_request(DEF_TWT_ID_T) );
}

void update_status_test() {
	test_request( _session->update_status_request(DEF_STR_T) );
}

void retweet_test() {
	test_request( _session->retweet_request(DEF_TWT_ID_T) );
}

void oembed_status_test() {
	test_request( _session->oembed_status_request(DEF_TWT_ID_T,DEF_STR_T) );
}

void search_tweets_test() {
	test_request( _session->search_tweets_request(DEF_STR_T) );
}

void sent_direct_messages_test() {
	test_request( _session->sent_direct_messages_request() );
}

void show_direct_messages_test() {
	test_request( _session->show_direct_messages_request(DEF_MSG_ID_T) );
}

void destroy_direct_messages_test() {
	test_request( _session->destroy_direct_messages_request(DEF_MSG_ID_T) );
}

void new_direct_message_by_id_test() {
	test_request( _session->new_direct_message_by_id_request(DEF_USR_ID_T,DEF_STR_T) );
}

void new_direct_message_test() {
	test_request( _session->new_direct_message_request(DEF_USR_NAME_T,DEF_STR_T) );
}

void friends_ids_by_id_test() {
	test_request( _session->friends_ids_by_id_request(DEF_USR_ID_T) );
}

void friends_ids_test() {
	test_request( _session->friends_ids_request(DEF_USR_NAME_T) );
}

void followers_ids_by_id_test() {
	test_request( _session->followers_ids_by_id_request(DEF_USR_ID_T) );
}

void followers_ids_test() {
	test_request( _session->followers_ids_request(DEF_USR_NAME_T) );
}

void lookup_friendship_test() {
	test_request( _session->lookup_friendship_request(DEF_USR_NAME_T) );
}

void lookup_friendship_by_ids_test() {
	test_request( _session->lookup_friendship_by_ids_request(DEF_USR_ID_T) );
}

void incoming_friendships_test() {
	test_request( _session->incoming_friendships_request() );
}

void outgoing_friendships_test() {
	test_request( _session->outgoing_friendships_request() );
}

void create_friendship_test() {
	test_request( _session->create_friendship_request(DEF_USR_NAME_T) );
}

void create_friendship_by_id_test() {
	test_request( _session->create_friendship_by_id_request(DEF_USR_ID_T) );
}

void destroy_friendship_test() {
	test_request( _session->destroy_friendship_request(DEF_USR_NAME_T) );
}

void destroy_friendship_by_id_test() {
	test_request( _session->destroy_friendship_by_id_request(DEF_USR_ID_T) );
}

void update_friendship_test() {
	test_request( _session->update_friendship_request(DEF_USR_NAME_T,DEF_BOOL,DEF_BOOL) );
}

void update_friendship_by_id_test() {
	test_request( _session->update_friendship_by_id_request(DEF_USR_ID_T,DEF_BOOL,DEF_BOOL) );
}

void show_friendship_test() {
	test_request( _session->show_friendship_request(DEF_USR_NAME_T,DEF_USR_NAME_T) );
}

void show_friendship_by_id_test() {
	test_request( _session->show_friendship_by_id_request(DEF_USR_ID_T,DEF_USR_ID_T) );
}

void verify_credentials_test() {
	test_request( _session->verify_credentials_request() );
}

void set_account_settings_test() {
	test_request( _session->set_account_settings_request() );
}

void update_delivery_device_test() {
	test_request( _session->update_delivery_device_request() );
}

void update_profile_test() {
	test_request( _session->update_profile_request() );
}

void update_profile_background_image_test() {
	test_request( _session->update_profile_background_image_request() );
}

void update_profile_colors_test() {
	test_request( _session->update_profile_colors_request() );
}

void get_blocks_list_test() {
	test_request( _session->get_blocks_list_request() );
}

void get_blocks_ids_test() {
	test_request( _session->get_blocks_ids_request() );
}

void create_blocks_test() {
	test_request( _session->create_blocks_request(DEF_USR_NAME_T) );
}

void create_blocks_by_id_test() {
	test_request( _session->create_blocks_by_id_request(DEF_USR_ID_T) );
}

void destroy_blocks_test() {
	test_request( _session->destroy_blocks_request(DEF_USR_NAME_T) );
}

void destroy_blocks_by_id_test() {
	test_request( _session->destroy_blocks_by_id_request(DEF_USR_ID_T) );
}

void lookup_user_by_id_test() {
	test_request( _session->lookup_user_by_id_request(DEF_USR_ID_T) );
}

void lookup_user_by_screen_name_test() {
	test_request( _session->lookup_user_by_screen_name_request(DEF_USR_NAME_T) );
}

void show_user_by_id_test() {
	test_request( _session->show_user_by_id_request(DEF_USR_ID_T) );
}

void show_user_test() {
	test_request( _session->show_user_request(DEF_USR_NAME_T) );
}

void search_user_test() {
	test_request( _session->search_user_request(DEF_STR_T) );
}

void user_contributees_by_user_id_test() {
	test_request( _session->user_contributees_by_user_id_request(DEF_USR_ID_T) );
}

void user_contributees_by_screen_name_test() {
	test_request( _session->user_contributees_by_screen_name_request(DEF_USR_NAME_T) );
}

void user_contributors_by_user_id_test() {
	test_request( _session->user_contributors_by_user_id_request(DEF_USR_ID_T) );
}

void user_contributors_by_screen_name_test() {
	test_request( _session->user_contributors_by_screen_name_request(DEF_USR_NAME_T) );
}

void user_suggestions_test() {
	test_request( _session->user_suggestions_request(DEF_SLUG_T) );
}

void user_suggestions_alt_test() {
	test_request( _session->user_suggestions_alt_request() );
}

void user_suggestions_members_test() {
	test_request( _session->user_suggestions_members_request(DEF_SLUG_T) );
}

void list_favorites_test() {
	test_request( _session->list_favorites_request() );
}

void list_favorites_by_screen_name_test() {
	test_request( _session->list_favorites_by_screen_name_request(DEF_USR_NAME_T) );
}

void destroy_favorite_test() {
	test_request( _session->destroy_favorite_request(DEF_TWT_ID_T) );
}

void create_favorite_test() {
	test_request( _session->create_favorite_request(DEF_TWT_ID_T) );
}

void lists_by_user_id_test() {
	test_request( _session->lists_by_user_id_request(DEF_USR_ID_T) );
}

void lists_test() {
	test_request( _session->lists_request(DEF_USR_ID_T) );
}

void list_statuses_by_ids_test() {
	test_request( _session->list_statuses_by_ids_request(DEF_LST_ID_T) );
}

void list_statuses_test() {
	test_request( _session->list_statuses_request(DEF_SLUG_T,DEF_USR_ID_T) );
}

void destroy_list_member_by_ids_test() {
	test_request( _session->destroy_list_member_by_ids_request(DEF_LST_ID_T,DEF_USR_ID_T) );
}

void destroy_list_member_test() {
	test_request( _session->destroy_list_member_request(DEF_SLUG_T,DEF_USR_ID_T) );
}

void list_membership_test() {
	test_request( _session->list_membership_request(DEF_USR_NAME_T) );
}

void list_membership_by_id_test() {
	test_request( _session->list_membership_by_id_request(DEF_USR_ID_T) );
}

void list_suscribers_test() {
	test_request( _session->list_suscribers_request(DEF_SLUG_T,DEF_USR_NAME_T,DEF_CUR_ID_T) );
}

void list_suscribers_by_id_test() {
	test_request( _session->list_suscribers_by_id_request(DEF_LST_ID_T,DEF_CUR_ID_T) );
}

void subscribe_to_list_test() {
	test_request( _session->subscribe_to_list_request(DEF_LST_ID_T) );
}

void subscribe_to_list_1_test() {
	test_request( _session->subscribe_to_list_request(DEF_SLUG_T,DEF_USR_NAME_T) );
}

void show_user_is_suscriber_by_ids_test() {
	test_request( _session->show_user_is_suscriber_by_ids_request(DEF_USR_ID_T,DEF_LST_ID_T) );
}

void show_user_is_suscriber_test() {
	test_request( _session->show_user_is_suscriber_request(DEF_USR_NAME_T,DEF_LST_ID_T,DEF_USR_NAME_T) );
}

void unsubscribe_from_list_test() {
	test_request( _session->unsubscribe_from_list_request(DEF_LST_ID_T) );
}

void unsubscribe_from_list_1_test() {
	test_request( _session->unsubscribe_from_list_request(DEF_SLUG_T,DEF_USR_NAME_T) );
}

void subscribe_to_list_multi_by_ids_test() {
	test_request( _session->subscribe_to_list_multi_by_ids_request(DEF_LST_ID_T,DEF_USR_ID_T) );
}

void subscribe_to_list_multi_test() {
	test_request( _session->subscribe_to_list_multi_request(DEF_SLUG_T,DEF_USR_NAME_T,DEF_USR_NAME_T) );
}

void show_user_is_member_by_ids_test() {
	test_request( _session->show_user_is_member_by_ids_request(DEF_LST_ID_T,DEF_USR_ID_T) );
}

void show_user_is_member_test() {
	test_request( _session->show_user_is_member_request(DEF_SLUG_T,DEF_USR_NAME_T,DEF_USR_NAME_T) );
}

void list_members_by_id_test() {
	test_request( _session->list_members_by_id_request(DEF_LST_ID_T) );
}

void list_members_test() {
	test_request( _session->list_members_request(DEF_SLUG_T,DEF_USR_NAME_T,DEF_CUR_ID_T) );
}

void join_list_test() {
	test_request( _session->join_list_request(DEF_USR_ID_T,DEF_LST_ID_T) );
}

void join_list_1_test() {
	test_request( _session->join_list_request(DEF_USR_NAME_T,DEF_SLUG_T,DEF_USR_NAME_T) );
}

void part_from_list_test() {
	test_request( _session->part_from_list_request(DEF_LST_ID_T) );
}

void update_list_by_id_test() {
	test_request( _session->update_list_by_id_request(DEF_LST_ID_T) );
}

void update_list_test() {
	test_request( _session->update_list_request(DEF_SLUG_T,DEF_USR_NAME_T) );
}

void create_list_test() {
	test_request( _session->create_list_request(DEF_STR_T) );
}

void show_list_test() {
	test_request( _session->show_list_request(DEF_LST_ID_T) );
}

void show_list_1_test() {
	test_request( _session->show_list_request(DEF_SLUG_T,DEF_USR_NAME_T) );
}

void lists_subscription_by_id_test() {
	test_request( _session->lists_subscription_by_id_request(DEF_USR_ID_T) );
}

void lists_subscription_test() {
	test_request( _session->lists_subscription_request(DEF_USR_NAME_T) );
}

void expulse_from_list_by_ids_test() {
	test_request( _session->expulse_from_list_by_ids_request(DEF_LST_ID_T,DEF_USR_ID_T) );
}

void expulse_from_list_test() {
	test_request( _session->expulse_from_list_request(DEF_SLUG_T,DEF_USR_NAME_T,DEF_USR_NAME_T) );
}

void get_saved_searches_test() {
	test_request( _session->get_saved_searches_request() );
}

void show_saved_search_test() {
	test_request( _session->show_saved_search_request(DEF_SCH_ID_T) );
}

void search_test() {
	test_request( _session->search_request(DEF_STR_T) );
}

void destroy_saved_search_test() {
	test_request( _session->destroy_saved_search_request(DEF_SCH_ID_T) );
}

void trends_place_test() {
	test_request( _session->trends_place_request(DEF_INT) );
}

void available_trends_test() {
	test_request( _session->available_trends_request() );
}

void closest_trend_test() {
	test_request( _session->closest_trend_request(DEF_FLOAT,DEF_FLOAT) );
}

void report_spam_test() {
	test_request( _session->report_spam_request(DEF_USR_ID_T) );
}

void rate_limit_status_test() {
	test_request( _session->rate_limit_status_request(DEF_STR_T) );
}

void help_languages_test() {
	test_request( _session->help_languages_request() );
}

void help_privacy_test() {
	test_request( _session->help_privacy_request() );
}

void help_TOS_test() {
	test_request( _session->help_TOS_request() );
}

void application_rate_limit_status_test() {
	test_request( _session->application_rate_limit_status_request() );
}

void user_stream_test() {
	test_request( _session->user_stream_request() );
}


/* END_PYGEN don't remove this comment (2012/10/27 14:35) */


    void start_tests() {
 
        CppUnit::TextTestResult result;
        suite()->run( &result );
        std::cout << "Tests results : " << result << std::endl;


		std::ofstream output_file(g_log_file.c_str());
		result.print(output_file);
		output_file.close();
    }


    private:

        TwitterSession* _session;




};

#endif /* _H_TEST_REQUESTS_H_ */