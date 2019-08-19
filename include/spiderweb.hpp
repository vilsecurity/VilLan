#pragma once
//! The spiderweb interconnect that forms the basis of villan

#include "spiderweb.grpc.pb.h"

#include "plugin.hpp"

#include <optional>

namespace VilSecurity::spiderweb {
  class storage : public proto::Storage::Service, public proto::Accessor::Service {
  public:
    grpc::Status store_commit(grpc::ServerContext* context,
                              grpc::ServerReader<proto::StoreCommitRequest>* reader,
                              proto::StoreCommitResponse* response) override;
    grpc::Status retrieve_epoch(grpc::ServerContext* context,
                                const proto::RetreiveEpochRequest* request,
                                grpc::ServerWriter<proto::RetreiveEpochResponse>* writer) override;

    grpc::Status retrieve_commit(grpc::ServerContext* context,
                                 const proto::RetrieveCommitRequest* request,
                                 grpc::ServerWriter<proto::RetrieveCommitResponse>* writer) override;
  };

  class master : public proto::Master::Service, public proto::Cabal::Service {
  public:
    grpc::Status notify_commit(grpc::ServerContext* context,
                               const proto::NotifyCommitRequest* request,
                               proto::NotifyCommitResponse* response) override;

    grpc::Status share(grpc::ServerContext* context,
                       grpc::ServerReader<proto::ShareRequest>* reader,
                       proto::ShareResponse* response) override;
    grpc::Status submit(grpc::ServerContext* context,
                        const proto::SubmitRequest* request,
                        proto::SubmitResponse* response) override;
    grpc::Status selected(grpc::ServerContext* context,
                          grpc::ServerReader<proto::SelectedRequest>* reader,
                          proto::SelectedResponse* response) override;
  };

  class worker : public proto::Worker::Service {
  public:
    grpc::Status notify_epoch(grpc::ServerContext* context,
                              const proto::NotifyEpochRequest* request,
                              proto::NotifyEpochResponse* response) override;
  };

  class controller {
  private:
    std::optional<storage> storage_aspect;
    std::optional<master> master_aspect;
    worker worker_aspect;
    villan::plugin exposed;

  public:
    controller(std::string plugin_iface, std::string cluster_iface);
  };
}
